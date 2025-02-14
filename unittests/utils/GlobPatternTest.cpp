//===- llvm/unittest/Support/GlobPatternTest.cpp --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// This source file is part of the polarphp.org open source project
// Copyright (c) 2017 - 2019 polarphp software foundation
// Copyright (c) 2017 - 2019 zzu_softboy <zzu_softboy@163.com>
// Licensed under Apache License v2.0 with Runtime Library Exception
// See https://polarphp.org/LICENSE.txt for license information
// See https://polarphp.org/CONTRIBUTORS.txt for the list of polarphp project authors
// Created by polarboy on 2018/07/13.

#include "polarphp/utils/GlobPattern.h"
#include "gtest/gtest.h"

using namespace polar::basic;
using namespace polar::utils;

namespace {

class GlobPatternTest : public ::testing::Test {};

TEST_F(GlobPatternTest, testBasics)
{
   Expected<GlobPattern> Pat1 = GlobPattern::create("");
   EXPECT_TRUE((bool)Pat1);
   EXPECT_TRUE(Pat1->match(""));
   EXPECT_FALSE(Pat1->match("a"));

   Expected<GlobPattern> Pat2 = GlobPattern::create("ab*c*def");
   EXPECT_TRUE((bool)Pat2);
   EXPECT_TRUE(Pat2->match("abcdef"));
   EXPECT_TRUE(Pat2->match("abxcxdef"));
   EXPECT_FALSE(Pat2->match(""));
   EXPECT_FALSE(Pat2->match("xabcdef"));
   EXPECT_FALSE(Pat2->match("abcdefx"));

   Expected<GlobPattern> Pat3 = GlobPattern::create("a??c");
   EXPECT_TRUE((bool)Pat3);
   EXPECT_TRUE(Pat3->match("axxc"));
   EXPECT_FALSE(Pat3->match("axxx"));
   EXPECT_FALSE(Pat3->match(""));

   Expected<GlobPattern> Pat4 = GlobPattern::create("[abc-fy-z]");
   EXPECT_TRUE((bool)Pat4);
   EXPECT_TRUE(Pat4->match("a"));
   EXPECT_TRUE(Pat4->match("b"));
   EXPECT_TRUE(Pat4->match("c"));
   EXPECT_TRUE(Pat4->match("d"));
   EXPECT_TRUE(Pat4->match("e"));
   EXPECT_TRUE(Pat4->match("f"));
   EXPECT_TRUE(Pat4->match("y"));
   EXPECT_TRUE(Pat4->match("z"));
   EXPECT_FALSE(Pat4->match("g"));
   EXPECT_FALSE(Pat4->match(""));

   Expected<GlobPattern> Pat5 = GlobPattern::create("[^abc-fy-z]");
   EXPECT_TRUE((bool)Pat5);
   EXPECT_TRUE(Pat5->match("g"));
   EXPECT_FALSE(Pat5->match("a"));
   EXPECT_FALSE(Pat5->match("b"));
   EXPECT_FALSE(Pat5->match("c"));
   EXPECT_FALSE(Pat5->match("d"));
   EXPECT_FALSE(Pat5->match("e"));
   EXPECT_FALSE(Pat5->match("f"));
   EXPECT_FALSE(Pat5->match("y"));
   EXPECT_FALSE(Pat5->match("z"));
   EXPECT_FALSE(Pat5->match(""));
}

TEST_F(GlobPatternTest, testInvalid)
{
   Expected<GlobPattern> Pat1 = GlobPattern::create("[");
   EXPECT_FALSE((bool)Pat1);
   handle_all_errors(Pat1.takeError(), [&](ErrorInfoBase &EIB) {});
}

TEST_F(GlobPatternTest, testExtSym)
{
   Expected<GlobPattern> Pat1 = GlobPattern::create("a*\xFF");
   EXPECT_TRUE((bool)Pat1);
   EXPECT_TRUE(Pat1->match("axxx\xFF"));
   Expected<GlobPattern> Pat2 = GlobPattern::create("[\xFF-\xFF]");
   EXPECT_TRUE((bool)Pat2);
   EXPECT_TRUE(Pat2->match("\xFF"));
}
} // anonymous namespace
