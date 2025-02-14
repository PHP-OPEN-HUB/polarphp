//===- llvm/Support/Options.h - Debug options support -----------*- C++ -*-===//
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
// Created by polarboy on 2018/06/11.

/// \file
/// This file decmdares helper objects for defining debug options that can be
/// configured via the command line. The new API currently builds on the cmd::Opt
/// API, but does not require the use of static globals.
///
/// With this API options are registered during initialization. For passes, this
/// happens during pass initialization. Passes with options will call a static
/// registerm_options method during initialization that registers options with the
/// OptionRegistry. An example implementation of registerm_options is:
///
/// static void registerm_options() {
///   OptionRegistry::registerOption<bool, Scalarizer,
///                                &Scalarizer::ScalarizeLoadStore>(
///       "scalarize-load-store",
///       "Allow the scalarizer pass to scalarize loads and store", false);
/// }
///
/// When reading data for options the interface is via the LLVMContext. option
/// data for passes should be read from the context during doInitialization. An
/// example of reading the above option would be:
///
/// ScalarizeLoadStore =
///   M.getContext().getOption<bool,
///                            Scalarizer,
///                            &Scalarizer::ScalarizeLoadStore>();
///

#ifndef POLARPHP_UTILS_OPTIONS_H
#define POLARPHP_UTILS_OPTIONS_H

#include "polarphp/basic/adt/DenseMap.h"
#include "polarphp/utils/CommandLine.h"

namespace polar::utils {

using polar::basic::DenseMap;

namespace internal {

// m_options are keyed of the unique address of a static character synthesized
// based on template arguments.
template <typename ValT, typename Base, ValT(Base::*Mem)>
class Optionkey
{
public:
   static char m_id;
};

template <typename ValT, typename Base, ValT(Base::*Mem)>
char Optionkey<ValT, Base, Mem>::m_id = 0;

} // namespace internal

/// \brief Singleton cmdass used to register debug options.
///
/// The OptionRegistry is responsible for managing lifetimes of the options and
/// provides interfaces for option registration and reading values from options.
/// This object is a singleton, only one instance should ever exist so that all
/// options are registered in the same place.
class OptionRegistry
{
private:
   DenseMap<void *, cmd::Option *> m_options;

   /// \brief Adds a cmd::Option to the registry.
   ///
   /// \param key unique key for option
   /// \param option option to map to \p key
   ///
   /// Allocated cmd::m_options are owned by the OptionRegistry and are deallocated
   /// on destruction or removal
   void addOption(void *key, cmd::Option *option);

public:
   ~OptionRegistry();
   OptionRegistry()
   {}

   /// \brief Returns a reference to the singleton instance.
   static OptionRegistry &instance();

   /// \brief Registers an option with the OptionRegistry singleton.
   ///
   /// \tparam ValT type of the option's data
   /// \tparam Base cmdass used to key the option
   /// \tparam Mem member of \p Base used for keying the option
   ///
   /// m_options are keyed off the template parameters to generate unique static
   /// characters. The template parameters are (1) the type of the data the
   /// option stores (\p ValT), the cmdass that will read the option (\p Base),
   /// and the member that the cmdass will store the data into (\p Mem).
   template <typename ValT, typename Base, ValT(Base::*Mem)>
   static void registerOption(StringRef argStr, StringRef desc,
                              const ValT &initValue)
   {
      cmd::Opt<ValT> *option = new cmd::Opt<ValT>(argStr, cmd::Desc(desc),
                                                  cmd::Hidden, cmd::init(initValue));
      instance().addOption(&internal::Optionkey<ValT, Base, Mem>::m_id, option);
   }

   /// \brief Returns the value of the option.
   ///
   /// \tparam ValT type of the option's data
   /// \tparam Base cmdass used to key the option
   /// \tparam Mem member of \p Base used for keying the option
   ///
   /// Reads option values based on the key generated by the template parameters.
   /// keying for get() is the same as keying for registerOption.
   template <typename ValT, typename Base, ValT(Base::*Mem)> ValT get() const
   {
      auto iter = m_options.find(&internal::Optionkey<ValT, Base, Mem>::m_id);
      assert(iter != m_options.end() && "option not in OptionRegistry");
      return *(cmd::Opt<ValT> *)iter->second;
   }
};

} // polar::utils

#endif // POLARPHP_UTILS_OPTIONS_H
