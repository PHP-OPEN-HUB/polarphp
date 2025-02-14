//===-- llvm/Support/TarWriter.h - Tar archive file creator -----*- C++ -*-===//
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

#ifndef POLARPHP_UTILS_TAR_WRITER_H
#define POLARPHP_UTILS_TAR_WRITER_H

#include "polarphp/basic/adt/StringRef.h"
#include "polarphp/basic/adt/StringSet.h"
#include "polarphp/utils/Error.h"
#include "polarphp/utils/RawOutStream.h"

namespace polar::utils {

using polar::basic::StringSet;

class TarWriter {
public:
   static Expected<std::unique_ptr<TarWriter>> create(StringRef outputPath,
                                                      StringRef baseDir);

   void append(StringRef path, StringRef data);

private:
   TarWriter(int fd, StringRef baseDir);
   RawFdOutStream m_outstream;
   std::string m_baseDir;
   StringSet<> m_files;
};

} // polar::utils

#endif // POLARPHP_UTILS_TAR_WRITER_H
