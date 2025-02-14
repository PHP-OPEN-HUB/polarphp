//=- CachePruning.h - Helper to manage the pruning of a cache dir -*- C++ -*-=//
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

#ifndef POLARPHP_UTILS_CACHE_PRUNING_H
#define POLARPHP_UTILS_CACHE_PRUNING_H

#include "polarphp/basic/adt/StringRef.h"
#include <chrono>
#include <optional>

namespace polar::utils {

using polar::basic::StringRef;

template <typename T> class Expected;

/// Policy for the pruneCache() function. A default constructed
/// CachePruningPolicy provides a reasonable default policy.
struct CachePruningPolicy
{
   /// The pruning interval. This is intended to be used to avoid scanning the
   /// directory too often. It does not impact the decision of which file to
   /// prune. A value of 0 forces the scan to occur. A value of None disables
   /// pruning.
   std::optional<std::chrono::seconds> m_interval = std::chrono::seconds(1200);

   /// The expiration for a file. When a file hasn't been accessed for expiration
   /// seconds, it is removed from the cache. A value of 0 disables the
   /// expiration-based pruning.
   std::chrono::seconds m_expiration = std::chrono::hours(7 * 24); // 1w

   /// The maximum size for the cache directory, in terms of percentage of the
   /// available space on the the disk. Set to 100 to indicate no limit, 50 to
   /// indicate that the cache size will not be left over half the available disk
   /// space. A value over 100 will be reduced to 100. A value of 0 disables the
   /// percentage size-based pruning.
   unsigned m_maxSizePercentageOfAvailableSpace = 75;

   /// The maximum size for the cache directory in bytes. A value over the amount
   /// of available space on the disk will be reduced to the amount of available
   /// space. A value of 0 disables the absolute size-based pruning.
   uint64_t m_maxSizeBytes = 0;

   /// The maximum number of files in the cache directory. A value of 0 disables
   /// the number of files based pruning.
   ///
   /// This defaults to 1000000 because with that many files there are
   /// diminishing returns on the effectiveness of the cache, and some file
   /// systems have a limit on how many files can be contained in a directory
   /// (notably ext4, which is limited to around 6000000 files).
   uint64_t m_maxSizeFiles = 1000000;
};

/// Parse the given string as a cache pruning policy. Defaults are taken from a
/// default constructed CachePruningPolicy object.
/// For example: "prune_interval=30s:prune_after=24h:cache_size=50%"
/// which means a pruning interval of 30 seconds, expiration time of 24 hours
/// and maximum cache size of 50% of available disk space.
Expected<CachePruningPolicy> parse_cache_pruning_policy(StringRef policyStr);

/// Peform pruning using the supplied policy, returns true if pruning
/// occured, i.e. if Policy.interval was expired.
///
/// As a safeguard against data loss if the user specifies the wrong directory
/// as their cache directory, this function will ignore files not matching the
/// pattern "llvmcache-*".
bool prune_cache(StringRef path, CachePruningPolicy policy);

} // polar::utils

#endif // POLARPHP_UTILS_CACHE_PRUNING_H
