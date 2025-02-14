//===-- SaveAndRestore.h - Utility  -------------------------------*- C++ -*-=//
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
// Created by polarboy on 2018/07/01.

#ifndef POLARPHP_UTILS_SAVE_AND_RESTORE_H
#define POLARPHP_UTILS_SAVE_AND_RESTORE_H

namespace polar::utils {

/// A utility class that uses RAII to save and restore the value of a variable.
template <typename T>
struct SaveAndRestore
{
   SaveAndRestore(T &value)
      : m_value(value),
        m_oldValue(value)
   {}
   SaveAndRestore(T &value, const T &newValue) : m_value(value), m_oldValue(value)
   {
      m_value = newValue;
   }
   ~SaveAndRestore()
   {
      m_value = m_oldValue;
   }

   T get()
   {
      return m_oldValue;
   }

private:
   T &m_value;
   T m_oldValue;
};

} // polar::utils

#endif // POLARPHP_UTILS_SAVE_AND_RESTORE_H
