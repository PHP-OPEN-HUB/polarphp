//===- llvm/unittest/ADT/SmallPtrSetTest.cpp ------------------------------===//
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
// Created by polarboy on 2018/07/06.

#include "polarphp/basic/adt/SmallPtrSet.h"
#include "polarphp/basic/adt/PointerIntPair.h"
#include "polarphp/utils/PointerLikeTypeTraits.h"
#include "gtest/gtest.h"

using namespace polar::basic;

namespace {

TEST(SmallPtrSetTest, testAssignment)
{
   int buf[8];
   for (int i = 0; i < 8; ++i) {
      buf[i] = 0;
   }
   SmallPtrSet<int *, 4> s1 = {&buf[0], &buf[1]};
   SmallPtrSet<int *, 4> s2;
   (s2 = s1).insert(&buf[2]);
   // Self assign as well.
   (s2 = s2).insert(&buf[3]);
   s1 = s2;
   EXPECT_EQ(4U, s1.getSize());
   for (int i = 0; i < 8; ++i) {
      if (i < 4) {
         EXPECT_TRUE(s1.count(&buf[i]));
      } else {
         EXPECT_FALSE(s1.count(&buf[i]));
      }
   }
   // Assign and insert with initializer lists, and ones that contain both
   // duplicates and out-of-order elements.
   (s2 = {&buf[6], &buf[7], &buf[6]}).insert({&buf[5], &buf[4]});
   for (int i = 0; i < 8; ++i) {
      if (i < 4) {
         EXPECT_FALSE(s2.count(&buf[i]));
      } else {
         EXPECT_TRUE(s2.count(&buf[i]));
      }
   }

}

TEST(SmallPtrSetTest, testGrowth)
{
   int i;
   int buf[8];
   for(i=0; i<8; ++i) {
      buf[i]=0;
   }
   SmallPtrSet<int *, 4> s;
   typedef SmallPtrSet<int *, 4>::iterator iter;
   s.insert(&buf[0]);
   s.insert(&buf[1]);
   s.insert(&buf[2]);
   s.insert(&buf[3]);
   EXPECT_EQ(4U, s.getSize());

   i = 0;
   for(iter I=s.begin(), E=s.end(); I!=E; ++I, ++i) {
      (**I)++;
   }

   EXPECT_EQ(4, i);
   for(i=0; i<8; ++i) {
      EXPECT_EQ(i<4?1:0,buf[i]);
   }
   s.insert(&buf[4]);
   s.insert(&buf[5]);
   s.insert(&buf[6]);
   s.insert(&buf[7]);

   i = 0;
   for(iter I=s.begin(), E=s.end(); I!=E; ++I, ++i) {
      (**I)++;
   }

   EXPECT_EQ(8, i);
   s.erase(&buf[4]);
   s.erase(&buf[5]);
   s.erase(&buf[6]);
   s.erase(&buf[7]);
   EXPECT_EQ(4U, s.getSize());

   i = 0;
   for(iter I=s.begin(), E=s.end(); I!=E; ++I, ++i)
      (**I)++;
   EXPECT_EQ(4, i);
   for(i=0; i<8; ++i)
      EXPECT_EQ(i<4?3:1,buf[i]);

   s.clear();
   for(i=0; i<8; ++i) buf[i]=0;
   for(i=0; i<128; ++i) s.insert(&buf[i%8]); // test repeated entires
   EXPECT_EQ(8U, s.getSize());
   for(iter I=s.begin(), E=s.end(); I!=E; ++I, ++i)
      (**I)++;
   for(i=0; i<8; ++i)
      EXPECT_EQ(1,buf[i]);
}

TEST(SmallPtrSetTest, testCopyAndMove)
{
   int buf[8];
   for (int i = 0; i < 8; ++i)
      buf[i] = 0;

   SmallPtrSet<int *, 4> s1;
   s1.insert(&buf[0]);
   s1.insert(&buf[1]);
   s1.insert(&buf[2]);
   s1.insert(&buf[3]);
   EXPECT_EQ(4U, s1.getSize());
   for (int i = 0; i < 8; ++i)
      if (i < 4)
         EXPECT_TRUE(s1.count(&buf[i]));
      else
         EXPECT_FALSE(s1.count(&buf[i]));

   SmallPtrSet<int *, 4> s2(s1);
   EXPECT_EQ(4U, s2.getSize());
   for (int i = 0; i < 8; ++i) {
      if (i < 4) {
         EXPECT_TRUE(s2.count(&buf[i]));
      } else {
         EXPECT_FALSE(s2.count(&buf[i]));
      }
   }
   s1 = s2;
   EXPECT_EQ(4U, s1.getSize());
   EXPECT_EQ(4U, s2.getSize());
   for (int i = 0; i < 8; ++i) {
      if (i < 4) {
         EXPECT_TRUE(s1.count(&buf[i]));
      } else {
         EXPECT_FALSE(s1.count(&buf[i]));
      }
   }
   SmallPtrSet<int *, 4> s3(std::move(s1));
   EXPECT_EQ(4U, s3.getSize());
   EXPECT_TRUE(s1.empty());
   for (int i = 0; i < 8; ++i) {
      if (i < 4) {
         EXPECT_TRUE(s3.count(&buf[i]));
      }  else {
         EXPECT_FALSE(s3.count(&buf[i]));
      }
   }
   // Move assign into the moved-from object. Also test move of a non-small
   // container.
   s3.insert(&buf[4]);
   s3.insert(&buf[5]);
   s3.insert(&buf[6]);
   s3.insert(&buf[7]);
   s1 = std::move(s3);
   EXPECT_EQ(8U, s1.getSize());
   EXPECT_TRUE(s3.empty());
   for (int i = 0; i < 8; ++i)
      EXPECT_TRUE(s1.count(&buf[i]));

   // Copy assign into a moved-from object.
   s3 = s1;
   EXPECT_EQ(8U, s3.getSize());
   EXPECT_EQ(8U, s1.getSize());
   for (int i = 0; i < 8; ++i)
      EXPECT_TRUE(s3.count(&buf[i]));
}

TEST(SmallPtrSetTest, testSwap) {
   int buf[10];

   SmallPtrSet<int *, 2> a;
   SmallPtrSet<int *, 2> b;

   a.insert(&buf[0]);
   a.insert(&buf[1]);
   b.insert(&buf[2]);

   EXPECT_EQ(2U, a.getSize());
   EXPECT_EQ(1U, b.getSize());
   EXPECT_TRUE(a.count(&buf[0]));
   EXPECT_TRUE(a.count(&buf[1]));
   EXPECT_FALSE(a.count(&buf[2]));
   EXPECT_FALSE(a.count(&buf[3]));
   EXPECT_FALSE(b.count(&buf[0]));
   EXPECT_FALSE(b.count(&buf[1]));
   EXPECT_TRUE(b.count(&buf[2]));
   EXPECT_FALSE(b.count(&buf[3]));

   std::swap(a, b);

   EXPECT_EQ(1U, a.getSize());
   EXPECT_EQ(2U, b.getSize());
   EXPECT_FALSE(a.count(&buf[0]));
   EXPECT_FALSE(a.count(&buf[1]));
   EXPECT_TRUE(a.count(&buf[2]));
   EXPECT_FALSE(a.count(&buf[3]));
   EXPECT_TRUE(b.count(&buf[0]));
   EXPECT_TRUE(b.count(&buf[1]));
   EXPECT_FALSE(b.count(&buf[2]));
   EXPECT_FALSE(b.count(&buf[3]));

   b.insert(&buf[3]);
   std::swap(a, b);

   EXPECT_EQ(3U, a.getSize());
   EXPECT_EQ(1U, b.getSize());
   EXPECT_TRUE(a.count(&buf[0]));
   EXPECT_TRUE(a.count(&buf[1]));
   EXPECT_FALSE(a.count(&buf[2]));
   EXPECT_TRUE(a.count(&buf[3]));
   EXPECT_FALSE(b.count(&buf[0]));
   EXPECT_FALSE(b.count(&buf[1]));
   EXPECT_TRUE(b.count(&buf[2]));
   EXPECT_FALSE(b.count(&buf[3]));

   std::swap(a, b);

   EXPECT_EQ(1U, a.getSize());
   EXPECT_EQ(3U, b.getSize());
   EXPECT_FALSE(a.count(&buf[0]));
   EXPECT_FALSE(a.count(&buf[1]));
   EXPECT_TRUE(a.count(&buf[2]));
   EXPECT_FALSE(a.count(&buf[3]));
   EXPECT_TRUE(b.count(&buf[0]));
   EXPECT_TRUE(b.count(&buf[1]));
   EXPECT_FALSE(b.count(&buf[2]));
   EXPECT_TRUE(b.count(&buf[3]));

   a.insert(&buf[4]);
   a.insert(&buf[5]);
   a.insert(&buf[6]);

   std::swap(b, a);

   EXPECT_EQ(3U, a.getSize());
   EXPECT_EQ(4U, b.getSize());
   EXPECT_TRUE(b.count(&buf[2]));
   EXPECT_TRUE(b.count(&buf[4]));
   EXPECT_TRUE(b.count(&buf[5]));
   EXPECT_TRUE(b.count(&buf[6]));
   EXPECT_TRUE(a.count(&buf[0]));
   EXPECT_TRUE(a.count(&buf[1]));
   EXPECT_TRUE(a.count(&buf[3]));
}

void checkEraseAndIterators(SmallPtrSetImpl<int*> &S)
{
   int buf[3];

   S.insert(&buf[0]);
   S.insert(&buf[1]);
   S.insert(&buf[2]);

   // Iterators must still be valid after erase() calls;
   auto B = S.begin();
   auto M = std::next(B);
   auto E = S.end();
   EXPECT_TRUE(*B == &buf[0] || *B == &buf[1] || *B == &buf[2]);
   EXPECT_TRUE(*M == &buf[0] || *M == &buf[1] || *M == &buf[2]);
   EXPECT_TRUE(*B != *M);
   int *Removable = *std::next(M);
   // No iterator points to Removable now.
   EXPECT_TRUE(Removable == &buf[0] || Removable == &buf[1] ||
         Removable == &buf[2]);
   EXPECT_TRUE(Removable != *B && Removable != *M);

   S.erase(Removable);

   // B,M,E iterators should still be valid
   EXPECT_EQ(B, S.begin());
   EXPECT_EQ(M, std::next(B));
   EXPECT_EQ(E, S.end());
   EXPECT_EQ(std::next(M), E);
}

TEST(SmallPtrSetTest, testEraseTest)
{
   // Test when set stays small.
   SmallPtrSet<int *, 8> B;
   checkEraseAndIterators(B);

   // Test when set grows big.
   SmallPtrSet<int *, 2> A;
   checkEraseAndIterators(A);
}

// Verify that dereferencing and iteration work.
TEST(SmallPtrSetTest, testDereferenceAndIterate)
{
   int Ints[] = {0, 1, 2, 3, 4, 5, 6, 7};
   SmallPtrSet<const int *, 4> S;
   for (int &I : Ints) {
      EXPECT_EQ(&I, *S.insert(&I).first);
      EXPECT_EQ(&I, *S.find(&I));
   }

   // Iterate from each and count how many times each element is found.
   int Found[sizeof(Ints)/sizeof(int)] = {0};
   for (int &I : Ints)
      for (auto F = S.find(&I), E = S.end(); F != E; ++F)
         ++Found[*F - Ints];

   // Sort.  We should hit the first element just once and the final element N
   // times.
   std::sort(std::begin(Found), std::end(Found));
   for (auto F = std::begin(Found), E = std::end(Found); F != E; ++F)
      EXPECT_EQ(F - Found + 1, *F);
}

// Verify that const pointers work for count and find even when the underlying
// SmallPtrSet is not for a const pointer type.
TEST(SmallPtrSetTest, testConstTest)
{
   SmallPtrSet<int *, 8> IntSet;
   int A;
   int *B = &A;
   const int *C = &A;
   IntSet.insert(B);
   EXPECT_EQ(IntSet.count(B), 1u);
   EXPECT_EQ(IntSet.count(C), 1u);
   EXPECT_NE(IntSet.find(B), IntSet.end());
   EXPECT_NE(IntSet.find(C), IntSet.end());
}

// Verify that we automatically get the const version of PointerLikeTypeTraits
// filled in for us, even for a non-pointer type
using TestPair = PointerIntPair<int *, 1>;

TEST(SmallPtrSetTest, testConstNonPtrTest)
{
   SmallPtrSet<TestPair, 8> IntSet;
   int A[1];
   TestPair Pair(&A[0], 1);
   IntSet.insert(Pair);
   EXPECT_EQ(IntSet.count(Pair), 1u);
   EXPECT_NE(IntSet.find(Pair), IntSet.end());
}

}


