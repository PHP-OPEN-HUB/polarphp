//===- X86TargetParser.def - X86 target parsing defines ---------*- C++ -*-===//
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
// Created by polarboy on 2018/10/17.

//===- X86TargetParser.def - X86 target parsing defines ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides defines to build up the X86 target parser's logic.
//
//===----------------------------------------------------------------------===//

// NOTE: NO INCLUDE GUARD DESIRED!

#ifndef X86_VENDOR
#define X86_VENDOR(ENUM, STR)
#endif
X86_VENDOR(VENDOR_INTEL, "intel")
X86_VENDOR(VENDOR_AMD,   "amd")
#undef X86_VENDOR

// This macro is used to implement CPU types that have an alias. As of now
// there is only ever one alias.
#ifndef X86_CPU_TYPE_COMPAT_WITH_ALIAS
#define X86_CPU_TYPE_COMPAT_WITH_ALIAS(ARCHNAME, ENUM, STR, ALIAS) X86_CPU_TYPE_COMPAT(ARCHNAME, ENUM, STR)
#endif

// This macro is used for cpu types present in compiler-rt/libgcc.
#ifndef X86_CPU_TYPE_COMPAT
#define X86_CPU_TYPE_COMPAT(ARCHNAME, ENUM, STR) X86_CPU_TYPE(ARCHNAME, ENUM)
#endif

#ifndef X86_CPU_TYPE
#define X86_CPU_TYPE(ARCHNAME, ENUM)
#endif
// The first part of this list must match what is implemented in libgcc and
// compilert-rt. Clang uses this to know how to implement __builtin_cpu_is.
X86_CPU_TYPE_COMPAT_WITH_ALIAS("bonnell",       INTEL_BONNELL,       "bonnell", "atom")
X86_CPU_TYPE_COMPAT           ("core2",         INTEL_CORE2,         "core2")
X86_CPU_TYPE_COMPAT           ("nehalem",       INTEL_COREI7,        "corei7")
X86_CPU_TYPE_COMPAT_WITH_ALIAS("amdfam10",      AMDFAM10H,           "amdfam10h", "amdfam10")
X86_CPU_TYPE_COMPAT_WITH_ALIAS("bdver1",        AMDFAM15H,           "amdfam15h", "amdfam15")
X86_CPU_TYPE_COMPAT_WITH_ALIAS("silvermont",    INTEL_SILVERMONT,    "silvermont", "slm")
X86_CPU_TYPE_COMPAT           ("knl",           INTEL_KNL,           "knl")
X86_CPU_TYPE_COMPAT           ("btver1",        AMD_BTVER1,          "btver1")
X86_CPU_TYPE_COMPAT           ("btver2",        AMD_BTVER2,          "btver2")
X86_CPU_TYPE_COMPAT           ("znver1",        AMDFAM17H,           "amdfam17h")
X86_CPU_TYPE_COMPAT           ("knm",           INTEL_KNM,           "knm")
X86_CPU_TYPE_COMPAT           ("goldmont",      INTEL_GOLDMONT,      "goldmont")
X86_CPU_TYPE_COMPAT           ("goldmont-plus", INTEL_GOLDMONT_PLUS, "goldmont-plus")
X86_CPU_TYPE_COMPAT           ("tremont",       INTEL_TREMONT,       "tremont")
// Entries below this are not in libgcc/compiler-rt.
X86_CPU_TYPE                  ("i386",        INTEL_i386)
X86_CPU_TYPE                  ("i486",        INTEL_i486)
X86_CPU_TYPE                  ("pentium",     INTEL_PENTIUM)
X86_CPU_TYPE                  ("pentium-mmx", INTEL_PENTIUM_MMX)
X86_CPU_TYPE                  ("pentiumpro",  INTEL_PENTIUM_PRO)
X86_CPU_TYPE                  ("pentium2",    INTEL_PENTIUM_II)
X86_CPU_TYPE                  ("pentium3",    INTEL_PENTIUM_III)
X86_CPU_TYPE                  ("pentium4",    INTEL_PENTIUM_IV)
X86_CPU_TYPE                  ("pentium-m",   INTEL_PENTIUM_M)
X86_CPU_TYPE                  ("yonah",       INTEL_CORE_DUO)
X86_CPU_TYPE                  ("nocona",      INTEL_NOCONA)
X86_CPU_TYPE                  ("prescott",    INTEL_PRESCOTT)
X86_CPU_TYPE                  ("i486",        AMD_i486)
X86_CPU_TYPE                  ("pentium",     AMDPENTIUM)
X86_CPU_TYPE                  ("athlon",      AMD_ATHLON)
X86_CPU_TYPE                  ("athlon-xp",   AMD_ATHLON_XP)
X86_CPU_TYPE                  ("k8",          AMD_K8)
X86_CPU_TYPE                  ("k8-sse3",     AMD_K8SSE3)
#undef X86_CPU_TYPE_COMPAT_WITH_ALIAS
#undef X86_CPU_TYPE_COMPAT
#undef X86_CPU_TYPE

// This macro is used for cpu subtypes present in compiler-rt/libgcc.
#ifndef X86_CPU_SUBTYPE_COMPAT
#define X86_CPU_SUBTYPE_COMPAT(ARCHNAME, ENUM, STR) X86_CPU_SUBTYPE(ARCHNAME, ENUM)
#endif

#ifndef X86_CPU_SUBTYPE
#define X86_CPU_SUBTYPE(ARCHNAME, ENUM)
#endif

// The first part of this list must match what is implemented in libgcc and
// compilert-rt. Clang uses this to know how to implement __builtin_cpu_is.
X86_CPU_SUBTYPE_COMPAT("nehalem",        INTEL_COREI7_NEHALEM,        "nehalem")
X86_CPU_SUBTYPE_COMPAT("westmere",       INTEL_COREI7_WESTMERE,       "westmere")
X86_CPU_SUBTYPE_COMPAT("sandybridge",    INTEL_COREI7_SANDYBRIDGE,    "sandybridge")
X86_CPU_SUBTYPE_COMPAT("amdfam10",       AMDFAM10H_BARCELONA,         "barcelona")
X86_CPU_SUBTYPE_COMPAT("amdfam10",       AMDFAM10H_SHANGHAI,          "shanghai")
X86_CPU_SUBTYPE_COMPAT("amdfam10",       AMDFAM10H_ISTANBUL,          "istanbul")
X86_CPU_SUBTYPE_COMPAT("bdver1",         AMDFAM15H_BDVER1,            "bdver1")
X86_CPU_SUBTYPE_COMPAT("bdver2",         AMDFAM15H_BDVER2,            "bdver2")
X86_CPU_SUBTYPE_COMPAT("bdver3",         AMDFAM15H_BDVER3,            "bdver3")
X86_CPU_SUBTYPE_COMPAT("bdver4",         AMDFAM15H_BDVER4,            "bdver4")
X86_CPU_SUBTYPE_COMPAT("znver1",         AMDFAM17H_ZNVER1,            "znver1")
X86_CPU_SUBTYPE_COMPAT("ivybridge",      INTEL_COREI7_IVYBRIDGE,      "ivybridge")
X86_CPU_SUBTYPE_COMPAT("haswell",        INTEL_COREI7_HASWELL,        "haswell")
X86_CPU_SUBTYPE_COMPAT("broadwell",      INTEL_COREI7_BROADWELL,      "broadwell")
X86_CPU_SUBTYPE_COMPAT("skylake",        INTEL_COREI7_SKYLAKE,        "skylake")
X86_CPU_SUBTYPE_COMPAT("skylake-avx512", INTEL_COREI7_SKYLAKE_AVX512, "skylake-avx512")
X86_CPU_SUBTYPE_COMPAT("cannonlake",     INTEL_COREI7_CANNONLAKE,     "cannonlake")
X86_CPU_SUBTYPE_COMPAT("icelake-client", INTEL_COREI7_ICELAKE_CLIENT, "icelake-client")
X86_CPU_SUBTYPE_COMPAT("icelake-server", INTEL_COREI7_ICELAKE_SERVER, "icelake-server")
X86_CPU_SUBTYPE_COMPAT("znver2",         AMDFAM17H_ZNVER2,            "znver2")
X86_CPU_SUBTYPE_COMPAT("cascadelake",    INTEL_COREI7_CASCADELAKE,    "cascadelake")
// Entries below this are not in libgcc/compiler-rt.
X86_CPU_SUBTYPE       ("core2",          INTEL_CORE2_65)
X86_CPU_SUBTYPE       ("penryn",         INTEL_CORE2_45)
X86_CPU_SUBTYPE       ("k6",             AMDPENTIUM_K6)
X86_CPU_SUBTYPE       ("k6-2",           AMDPENTIUM_K62)
X86_CPU_SUBTYPE       ("k6-3",           AMDPENTIUM_K63)
X86_CPU_SUBTYPE       ("geode",          AMDPENTIUM_GEODE)
X86_CPU_SUBTYPE       ("cooperlake",     INTEL_COREI7_COOPERLAKE)
#undef X86_CPU_SUBTYPE_COMPAT
#undef X86_CPU_SUBTYPE


// This macro is used for cpu types present in compiler-rt/libgcc.
#ifndef X86_FEATURE_COMPAT
#define X86_FEATURE_COMPAT(VAL, ENUM, STR) X86_FEATURE(VAL, ENUM)
#endif

#ifndef X86_FEATURE
#define X86_FEATURE(VAL, ENUM)
#endif
X86_FEATURE_COMPAT( 0, FEATURE_CMOV,            "cmov")
X86_FEATURE_COMPAT( 1, FEATURE_MMX,             "mmx")
X86_FEATURE_COMPAT( 2, FEATURE_POPCNT,          "popcnt")
X86_FEATURE_COMPAT( 3, FEATURE_SSE,             "sse")
X86_FEATURE_COMPAT( 4, FEATURE_SSE2,            "sse2")
X86_FEATURE_COMPAT( 5, FEATURE_SSE3,            "sse3")
X86_FEATURE_COMPAT( 6, FEATURE_SSSE3,           "ssse3")
X86_FEATURE_COMPAT( 7, FEATURE_SSE4_1,          "sse4.1")
X86_FEATURE_COMPAT( 8, FEATURE_SSE4_2,          "sse4.2")
X86_FEATURE_COMPAT( 9, FEATURE_AVX,             "avx")
X86_FEATURE_COMPAT(10, FEATURE_AVX2,            "avx2")
X86_FEATURE_COMPAT(11, FEATURE_SSE4_A,          "sse4a")
X86_FEATURE_COMPAT(12, FEATURE_FMA4,            "fma4")
X86_FEATURE_COMPAT(13, FEATURE_XOP,             "xop")
X86_FEATURE_COMPAT(14, FEATURE_FMA,             "fma")
X86_FEATURE_COMPAT(15, FEATURE_AVX512F,         "avx512f")
X86_FEATURE_COMPAT(16, FEATURE_BMI,             "bmi")
X86_FEATURE_COMPAT(17, FEATURE_BMI2,            "bmi2")
X86_FEATURE_COMPAT(18, FEATURE_AES,             "aes")
X86_FEATURE_COMPAT(19, FEATURE_PCLMUL,          "pclmul")
X86_FEATURE_COMPAT(20, FEATURE_AVX512VL,        "avx512vl")
X86_FEATURE_COMPAT(21, FEATURE_AVX512BW,        "avx512bw")
X86_FEATURE_COMPAT(22, FEATURE_AVX512DQ,        "avx512dq")
X86_FEATURE_COMPAT(23, FEATURE_AVX512CD,        "avx512cd")
X86_FEATURE_COMPAT(24, FEATURE_AVX512ER,        "avx512er")
X86_FEATURE_COMPAT(25, FEATURE_AVX512PF,        "avx512pf")
X86_FEATURE_COMPAT(26, FEATURE_AVX512VBMI,      "avx512vbmi")
X86_FEATURE_COMPAT(27, FEATURE_AVX512IFMA,      "avx512ifma")
X86_FEATURE_COMPAT(28, FEATURE_AVX5124VNNIW,    "avx5124vnniw")
X86_FEATURE_COMPAT(29, FEATURE_AVX5124FMAPS,    "avx5124fmaps")
X86_FEATURE_COMPAT(30, FEATURE_AVX512VPOPCNTDQ, "avx512vpopcntdq")
X86_FEATURE_COMPAT(31, FEATURE_AVX512VBMI2,     "avx512vbmi2")
X86_FEATURE_COMPAT(32, FEATURE_GFNI,            "gfni")
X86_FEATURE_COMPAT(33, FEATURE_VPCLMULQDQ,      "vpclmulqdq")
X86_FEATURE_COMPAT(34, FEATURE_AVX512VNNI,      "avx512vnni")
X86_FEATURE_COMPAT(35, FEATURE_AVX512BITALG,    "avx512bitalg")

// Features below here are not in libgcc/compiler-rt.
X86_FEATURE       (64, FEATURE_MOVBE)
X86_FEATURE       (65, FEATURE_ADX)
X86_FEATURE       (66, FEATURE_EM64T)
X86_FEATURE       (67, FEATURE_CLFLUSHOPT)
X86_FEATURE       (68, FEATURE_SHA)
X86_FEATURE       (69, FEATURE_AVX512BF16)
#undef X86_FEATURE_COMPAT
#undef X86_FEATURE
