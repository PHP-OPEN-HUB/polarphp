//===- SystemUtils.h - Utilities to do low-level system stuff ---*- C++ -*-===//
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
// Created by polarboy on 2018/07/04.

#ifndef POLARPHP_UTILS_SYSTEM_UTILS_H
#define POLARPHP_UTILS_SYSTEM_UTILS_H

namespace polar::utils {

class RawOutStream;

/// Determine if the RawOutStream provided is connected to a terminal. If so,
/// generate a warning message to errs() advising against display of bitcode
/// and return true. Otherwise just return false.
/// @brief Check for output written to a console
bool check_bitcode_output_to_console(
      RawOutStream &streamToCheck, ///< The stream to be checked
      bool printWarning = true     ///< Control whether warnings are printed
      );

} // polar::utils

#endif // POLARPHP_UTILS_SYSTEM_UTILS_H
