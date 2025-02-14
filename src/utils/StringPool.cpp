//===-- StringPool.cpp - Interned string pool -----------------------------===//
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

#include "polarphp//utils/StringPool.h"
#include "polarphp/basic/adt/StringRef.h"

namespace polar::utils {

StringPool::StringPool()
{}

StringPool::~StringPool()
{
   assert(m_internTable.empty() && "PooledStringPtr leaked!");
}

PooledStringPtr StringPool::intern(StringRef key)
{
   TableType::iterator iter = m_internTable.find(key);
   if (iter != m_internTable.end()) {
      return PooledStringPtr(&*iter);
   }

   EntryType *entryStr = EntryType::create(key);
   entryStr->getValue().m_pool = this;
   m_internTable.insert(entryStr);
   return PooledStringPtr(entryStr);
}

} // polar::utils
