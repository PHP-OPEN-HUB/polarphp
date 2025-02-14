//===-- llvm/Support/PluginLoader.h - Plugin Loader for Tools ---*- C++ -*-===//
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

#ifndef POLARPHP_UTILS_PLIGIN_LOADER_H
#define POLARPHP_UTILS_PLIGIN_LOADER_H

#include "polarphp/utils/CommandLine.h"

namespace polar::utils {

struct PluginLoader
{
   void operator=(const std::string &filename);
   static unsigned getNumPlugins();
   static std::string& getPlugin(unsigned num);
};

#ifndef DONT_GET_PLUGIN_LOADER_OPTION
// This causes operator= above to be invoked for every -load option.
static cmd::Opt<PluginLoader, false, cmd::Parser<std::string>>
sg_loadOpt("load", cmd::ZeroOrMore, cmd::ValueDesc("pluginfilename"),
           cmd::Desc("Load the specified plugin"));
#endif

} // polar::utils

#endif // POLARPHP_UTILS_PLIGIN_LOADER_H
