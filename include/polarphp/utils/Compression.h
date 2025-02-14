//===-- llvm/Support/Compression.h ---Compression----------------*- C++ -*-===//
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

#ifndef POLARPHP_UTILS_COMPRESSION_H
#define POLARPHP_UTILS_COMPRESSION_H

#include "polarphp/global/DataTypes.h"

namespace polar::basic {
// forward declare class with namespace
class StringRef;
template <typename T> class SmallVectorImpl;
} // basic

namespace polar::utils {

class Error;

using polar::basic::StringRef;
using polar::basic::SmallVectorImpl;

namespace zlib {

static constexpr int NoCompression = 0;
static constexpr int BestSpeedCompression = 1;
static constexpr int DefaultCompression = 6;
static constexpr int BestSizeCompression = 9;

bool is_available();

Error compress(StringRef inputBuffer, SmallVectorImpl<char> &compressedBuffer,
               int level = DefaultCompression);

Error uncompress(StringRef inputBuffer, char *uncompressedBuffer,
                 size_t &uncompressedSize);

Error uncompress(StringRef inputBuffer,
                 SmallVectorImpl<char> &uncompressedBuffer,
                 size_t uncompressedSize);

uint32_t crc32(StringRef buffer);

}  // End of namespace zlib

} // polar::utils

#endif // POLARPHP_UTILS_COMPRESSION_H
