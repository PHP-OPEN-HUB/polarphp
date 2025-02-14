//===--- Capacity.h - Generic computation of ADT memory use -----*- C++ -*-===//
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
// Created by polarboy on 2018/06/29.

#ifndef POLARPHP_UTILS_CAPACITY_H
#define POLARPHP_UTILS_CAPACITY_H

#include <cstddef>

namespace polar::utils {

template <typename T>
static inline size_t capacity_in_bytes(const T &object)
{
   // This default definition of capacity should work for things like std::vector
   // and friends.  More specialized versions will work for others.
   return object.getCapacity() * sizeof(typename T::value_type);
}

} // polar::utils

#endif // POLARPHP_UTILS_CAPACITY_H
