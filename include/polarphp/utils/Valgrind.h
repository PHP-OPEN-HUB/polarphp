//===- llvm/Support/Valgrind.h - Communication with Valgrind ----*- C++ -*-===//
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

#ifndef POLARPHP_UTILS_VALGRIND_H
#define POLARPHP_UTILS_VALGRIND_H

#include <cstddef>

//===----------------------------------------------------------------------===//
//
// Methods for communicating with a valgrind instance this program is running
// under.  These are all no-ops unless LLVM was configured on a system with the
// valgrind headers installed and valgrind is controlling this process.
//
//===----------------------------------------------------------------------===//

namespace polar::sys {

// True if Valgrind is controlling this process.
bool running_on_valgrind();

// Discard valgrind's translation of code in the range [Addr .. Addr + Len).
// Otherwise valgrind may continue to execute the old version of the code.
void valgrind_discard_translations(const void *addr, size_t len);

} // polar::sys

#endif // POLARPHP_UTILS_VALGRIND_H
