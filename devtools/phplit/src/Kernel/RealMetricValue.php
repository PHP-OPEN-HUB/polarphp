<?php
// This source file is part of the polarphp.org open source project
//
// Copyright (c) 2017 - 2019 polarphp software foundation
// Copyright (c) 2017 - 2019 zzu_softboy <zzu_softboy@163.com>
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://polarphp.org/LICENSE.txt for license information
// See https://polarphp.org/CONTRIBUTORS.txt for the list of polarphp project authors
//
// Created by polarboy on 2019/10/10.

namespace Lit\Kernel;

class RealMetricValue extends AbstractMetricValue
{
   public function format() : string
   {
      return sprintf('%.4f', $this->value);
   }

   public function toData()
   {
      return $this->value;
   }
}