//===- llvm/unittest/Support/DebugCounterTest.cpp -------------------------===//
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
// Created by polarboy on 2018/10/22.

#include "polarphp/utils/DebugCounter.h"
#include "gtest/gtest.h"

#include <string>
using namespace polar::utils;

#ifndef NDEBUG

TEST(DebugCounterTest, testCounterCheck)
{
   DEBUG_COUNTER(TestCounter, "test-counter", "Counter used for unit test");
   EXPECT_FALSE(DebugCounter::isCounterSet(TestCounter));

   auto DC = &DebugCounter::getInstance();
   DC->pushBack("test-counter-skip=1");
   DC->pushBack("test-counter-count=3");

   EXPECT_TRUE(DebugCounter::isCounterSet(TestCounter));

   EXPECT_EQ(0, DebugCounter::getCounterValue(TestCounter));
   EXPECT_FALSE(DebugCounter::shouldExecute(TestCounter));

   EXPECT_EQ(1, DebugCounter::getCounterValue(TestCounter));
   EXPECT_TRUE(DebugCounter::shouldExecute(TestCounter));

   DebugCounter::setCounterValue(TestCounter, 3);
   EXPECT_TRUE(DebugCounter::shouldExecute(TestCounter));
   EXPECT_FALSE(DebugCounter::shouldExecute(TestCounter));

   DebugCounter::setCounterValue(TestCounter, 100);
   EXPECT_FALSE(DebugCounter::shouldExecute(TestCounter));
}
#endif
