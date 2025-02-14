//===- llvm/unittest/ADT/PointerUnionTest.cpp - Optional unit tests -------===//
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
// Created by polarboy on 2018/07/08.

#include "polarphp/basic/adt/PointerUnion.h"
#include "gtest/gtest.h"

using namespace polar::basic;

namespace {

typedef PointerUnion<int *, float *> PU;

struct PointerUnionTest : public testing::Test
{
   float f;
   int i;

   PU a, b, c, n;

   PointerUnionTest() : f(3.14f), i(42), a(&f), b(&i), c(&i), n() {}
};

TEST_F(PointerUnionTest, testComparison)
{
   EXPECT_TRUE(a == a);
   EXPECT_FALSE(a != a);
   EXPECT_TRUE(a != b);
   EXPECT_FALSE(a == b);
   EXPECT_TRUE(b == c);
   EXPECT_FALSE(b != c);
   EXPECT_TRUE(b != n);
   EXPECT_FALSE(b == n);
}

TEST_F(PointerUnionTest, testNull)
{
   EXPECT_FALSE(a.isNull());
   EXPECT_FALSE(b.isNull());
   EXPECT_TRUE(n.isNull());
   EXPECT_FALSE(!a);
   EXPECT_FALSE(!b);
   EXPECT_TRUE(!n);
   // workaround an issue with EXPECT macros and explicit bool
   EXPECT_TRUE((bool)a);
   EXPECT_TRUE((bool)b);
   EXPECT_FALSE(n);

   EXPECT_NE(n, b);
   EXPECT_EQ(b, c);
   b = nullptr;
   EXPECT_EQ(n, b);
   EXPECT_NE(b, c);
}

TEST_F(PointerUnionTest, testIs)
{
   EXPECT_FALSE(a.is<int *>());
   EXPECT_TRUE(a.is<float *>());
   EXPECT_TRUE(b.is<int *>());
   EXPECT_FALSE(b.is<float *>());
   EXPECT_TRUE(n.is<int *>());
   EXPECT_FALSE(n.is<float *>());
}

TEST_F(PointerUnionTest, testGet)
{
   EXPECT_EQ(a.get<float *>(), &f);
   EXPECT_EQ(b.get<int *>(), &i);
   EXPECT_EQ(n.get<int *>(), (int *)nullptr);
}

template<int I> struct alignas(8) Aligned {};

typedef PointerUnion<Aligned<0> *, Aligned<1> *, Aligned<2> *, Aligned<3> *,
Aligned<4> *, Aligned<5> *, Aligned<6> *, Aligned<7> *>
PU8;

TEST_F(PointerUnionTest, testManyElements) {
   Aligned<0> a0;
   Aligned<7> a7;

   PU8 a = &a0;
   EXPECT_TRUE(a.is<Aligned<0>*>());
   EXPECT_FALSE(a.is<Aligned<1>*>());
   EXPECT_FALSE(a.is<Aligned<2>*>());
   EXPECT_FALSE(a.is<Aligned<3>*>());
   EXPECT_FALSE(a.is<Aligned<4>*>());
   EXPECT_FALSE(a.is<Aligned<5>*>());
   EXPECT_FALSE(a.is<Aligned<6>*>());
   EXPECT_FALSE(a.is<Aligned<7>*>());
   EXPECT_EQ(a.dynamicCast<Aligned<0>*>(), &a0);
   EXPECT_EQ(*a.getAddrOfPtr1(), &a0);

   a = &a7;
   EXPECT_FALSE(a.is<Aligned<0>*>());
   EXPECT_FALSE(a.is<Aligned<1>*>());
   EXPECT_FALSE(a.is<Aligned<2>*>());
   EXPECT_FALSE(a.is<Aligned<3>*>());
   EXPECT_FALSE(a.is<Aligned<4>*>());
   EXPECT_FALSE(a.is<Aligned<5>*>());
   EXPECT_FALSE(a.is<Aligned<6>*>());
   EXPECT_TRUE(a.is<Aligned<7>*>());
   EXPECT_EQ(a.dynamicCast<Aligned<7>*>(), &a7);

   EXPECT_TRUE(a == PU8(&a7));
   EXPECT_TRUE(a != PU8(&a0));
}

} // anonymous namespace
