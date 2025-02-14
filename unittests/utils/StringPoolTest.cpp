//===- llvm/unittest/Support/StringPoiil.cpp - StringPool tests -----------===//
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
// Created by polarboy on 2018/07/15.

#include "polarphp/utils/StringPool.h"
#include "gtest/gtest.h"

using namespace polar;
using namespace polar::basic;
using namespace polar::utils;

namespace {

TEST(PooledStringPtrTest, testOperatorEquals)
{
   StringPool pool;
   const PooledStringPtr a = pool.intern("a");
   const PooledStringPtr b = pool.intern("b");
   EXPECT_FALSE(a == b);
}

TEST(PooledStringPtrTest, testOperatorNotEquals)
{
   StringPool pool;
   const PooledStringPtr a = pool.intern("a");
   const PooledStringPtr b = pool.intern("b");
   EXPECT_TRUE(a != b);
}

} // anonymous namespace
