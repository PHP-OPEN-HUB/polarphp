//===- Unix/Memory.cpp - Generic UNIX System Configuration ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// This source file is part of the polarphp.org open source project
//
// Copyright (c) 2017 - 2019 polarphp software foundation
// Copyright (c) 2017 - 2019 zzu_softboy <zzu_softboy@163.com>
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://polarphp.org/LICENSE.txt for license information
// See https://polarphp.org/CONTRIBUTORS.txt for the list of polarphp project authors
//
// Created by polarboy on 2018/06/21.

//===----------------------------------------------------------------------===//
//
// This file defines some helpful functions for allocating memory and dealing
// with memory mapped files
//
//===----------------------------------------------------------------------===//

#include "polarphp/global/Config.h"
#include "polarphp/utils/unix/Unix.h"
#include "polarphp/global/DataTypes.h"
#include "polarphp/utils/ErrorHandling.h"
#include "polarphp/utils/Process.h"
#include "polarphp/utils/Memory.h"
#include "polarphp/utils/Valgrind.h"
#include "polarphp/utils/MathExtras.h"

#ifdef POLAR_HAVE_SYS_MMAN_H
#include <sys/mman.h>
#endif

#ifdef __APPLE__
#include <mach/mach.h>
#endif

#ifdef __Fuchsia__
#include <zircon/syscalls.h>
#endif

#if defined(__mips__)
#  if defined(__OpenBSD__)
#    include <mips64/sysarch.h>
#  elif !defined(__FreeBSD__)
#    include <sys/cachectl.h>
#  endif
#endif

#ifdef __APPLE__
extern "C" void sys_icache_invalidate(const void *addr, size_t len);
#else
extern "C" void __clear_cache(void *, void*);
#endif

namespace polar::sys {

using polar::utils::align_addr;

namespace {

int get_posix_protection_flags(unsigned flags)
{
   switch (flags & Memory::MF_RWE_MASK) {
   case Memory::MF_READ:
      return PROT_READ;
   case Memory::MF_WRITE:
      return PROT_WRITE;
   case Memory::MF_READ | Memory::MF_WRITE:
      return PROT_READ | PROT_WRITE;
   case Memory::MF_READ | Memory::MF_EXEC:
      return PROT_READ | PROT_EXEC;
   case Memory::MF_READ | Memory::MF_WRITE |
   Memory::MF_EXEC:
      return PROT_READ | PROT_WRITE | PROT_EXEC;
   case Memory::MF_EXEC:
#if (defined(__FreeBSD__) || defined(__POWERPC__) || defined (__ppc__) || \
   defined(_POWER) || defined(_ARCH_PPC))
      // On PowerPC, having an executable page that has no read permission
      // can have unintended consequences.  The function InvalidateInstruction-
      // Cache uses instructions dcbf and icbi, both of which are treated by
      // the processor as loads.  If the page has no read permissions,
      // executing these instructions will result in a segmentation fault.
      return PROT_READ | PROT_EXEC;
#else
      return PROT_EXEC;
#endif
   default:
      polar_unreachable("Illegal memory protection flag specified!");
   }
   // Provide a default return value as required by some compilers.
   return PROT_NONE;
}

} // anonymous namespace

MemoryBlock
Memory::allocateMappedMemory(size_t numBytes,
                             const MemoryBlock *const nearBlock,
                             unsigned pflags,
                             std::error_code &errorCode)
{
   errorCode = std::error_code();
   if (numBytes == 0) {
      return MemoryBlock();
   }

   // On platforms that have it, we can use MAP_ANON to get a memory-mapped
   // page without file backing, but we need a fallback of opening /dev/zero
   // for strictly POSIX platforms instead.
   int fd;
#if defined(MAP_ANON)
   fd = -1;
#else
   fd = open("/dev/zero", O_RDWR);
   if (fd == -1) {
      EC = std::error_code(errno, std::generic_category());
      return MemoryBlock();
   }
#endif

   int mmFlags = MAP_PRIVATE;
#if defined(MAP_ANON)
   mmFlags |= MAP_ANON;
#endif
   int protect = get_posix_protection_flags(pflags);

#if defined(__NetBSD__) && defined(PROT_MPROTECT)
   protect |= PROT_MPROTECT(PROT_READ | PROT_WRITE | PROT_EXEC);
#endif

   // Use any near hint and the page size to set a page-aligned starting address
   uintptr_t start = nearBlock ? reinterpret_cast<uintptr_t>(nearBlock->getBase()) +
                                 nearBlock->getAllocatedSize() : 0;
   static const size_t pageSize = Process::getPageSizeEstimate();
   const size_t numPages = (numBytes+pageSize-1)/pageSize;

   if (start && start % pageSize)
      start += pageSize - start % pageSize;

   // FIXME: Handle huge page requests (MF_HUGE_HINT).
   void *addr = ::mmap(reinterpret_cast<void *>(start), pageSize*numPages, protect,
                       mmFlags, fd, 0);
   if (addr == MAP_FAILED) {
      if (nearBlock) { //Try again without a near hint
#if !defined(MAP_ANON)
         close(fd);
#endif
         return allocateMappedMemory(numBytes, nullptr, pflags, errorCode);
      }
      errorCode = std::error_code(errno, std::generic_category());
#if !defined(MAP_ANON)
      close(fd);
#endif
      return MemoryBlock();
   }

#if !defined(MAP_ANON)
   close(fd);
#endif

   MemoryBlock result;
   result.m_address = addr;
   result.m_allocatedSize = pageSize*numPages;
   result.m_flags = pflags;

   // Rely on protectMappedMemory to invalidate instruction cache.
   if (pflags & MF_EXEC) {
      errorCode = Memory::protectMappedMemory (result, pflags);
      if (errorCode != std::error_code()) {
         return MemoryBlock();
      }
   }
   return result;
}

std::error_code
Memory::releaseMappedMemory(MemoryBlock &block)
{
   if (block.m_address == nullptr || block.m_allocatedSize == 0) {
      return std::error_code();
   }
   if (0 != ::munmap(block.m_address, block.m_allocatedSize)) {
      return std::error_code(errno, std::generic_category());
   }
   block.m_address = nullptr;
   block.m_allocatedSize = 0;
   return std::error_code();
}

std::error_code
Memory::protectMappedMemory(const MemoryBlock &block, unsigned flags)
{
   static const size_t pageSize = Process::getPageSizeEstimate();
   if (block.m_address == nullptr || block.m_allocatedSize == 0) {
       return std::error_code();
   }
   if (!flags) {
      return std::error_code(EINVAL, std::generic_category());
   }
   int Protect = get_posix_protection_flags(flags);
   uintptr_t start = align_addr((uint8_t *)block.m_address - pageSize + 1, pageSize);
   uintptr_t end = align_addr((uint8_t *)block.m_address + block.m_allocatedSize, pageSize);
   bool invalidateCache = (flags & MF_EXEC);
#if defined(__arm__) || defined(__aarch64__)
   // Certain ARM implementations treat icache clear instruction as a memory read,
   // and CPU segfaults on trying to clear cache on !PROT_READ page.  Therefore we need
   // to temporarily add PROT_READ for the sake of flushing the instruction caches.
   if (invalidateCache && !(Protect & PROT_READ)) {
      int result = ::mprotect((void *)start, end - start, Protect | PROT_READ);
      if (result != 0)
         return std::error_code(errno, std::generic_category());

      Memory::invalidateInstructionCache(block.m_address, block.m_allocatedSize);
      invalidateCache = false;
   }
#endif
   int result = ::mprotect((void *)start, end - start, Protect);
   if (result != 0) {
       return std::error_code(errno, std::generic_category());
   }
   if (invalidateCache) {
       Memory::invalidateInstructionCache(block.m_address, block.m_allocatedSize);
   }
   return std::error_code();
}

/// invalidateInstructionCache - Before the JIT can run a block of code
/// that has been emitted it must invalidate the instruction cache on some
/// platforms.
void Memory::invalidateInstructionCache(const void *addr,
                                        size_t len)
{

   // icache invalidation for PPC and ARM.
#if defined(__APPLE__)

#  if (defined(__POWERPC__) || defined (__ppc__) || \
   defined(_POWER) || defined(_ARCH_PPC) || defined(__arm__) || \
   defined(__arm64__))
   sys_icache_invalidate(const_cast<void *>(addr), Len);
#  endif
#elif defined(__Fuchsia__)

   zx_status_t Status = zx_cache_flush(addr, Len, ZX_CACHE_FLUSH_INSN);
   assert(Status == ZX_OK && "cannot invalidate instruction cache");
#else

#  if (defined(__POWERPC__) || defined (__ppc__) || \
   defined(_POWER) || defined(_ARCH_PPC)) && defined(__GNUC__)
   const size_t LineSize = 32;

   const intptr_t Mask = ~(LineSize - 1);
   const intptr_t startLine = ((intptr_t) addr) & Mask;
   const intptr_t EndLine = ((intptr_t) addr + Len + LineSize - 1) & Mask;

   for (intptr_t Line = startLine; Line < EndLine; Line += LineSize)
      asm volatile("dcbf 0, %0" : : "r"(Line));
   asm volatile("sync");

   for (intptr_t Line = startLine; Line < EndLine; Line += LineSize)
      asm volatile("icbi 0, %0" : : "r"(Line));
   asm volatile("isync");
#  elif (defined(__arm__) || defined(__aarch64__) || defined(__mips__)) && \
   defined(__GNUC__)
   // FIXME: Can we safely always call this for __GNUC__ everywhere?
   const char *start = static_cast<const char *>(addr);
   const char *end = start + Len;
   __clear_cache(const_cast<char *>(start), const_cast<char *>(end));
#  endif

#endif  // end apple

   valgrind_discard_translations(addr, len);
}

} // polar::sys
