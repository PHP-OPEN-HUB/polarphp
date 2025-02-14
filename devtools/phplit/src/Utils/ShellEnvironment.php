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
// Created by polarboy on 2019/10/12.
namespace Lit\Utils;
/**
 * Mutable shell environment containing things like CWD and env vars.
 * Environment variables are not implemented, but cwd tracking is.
 *
 * @package Lit\Utils
 */
class ShellEnvironment
{
   /**
    * @var string $cwd
    */
   private $cwd;
   /**
    * @var array $env
    */
   private $env;

   public function __construct(string $cwd, array $env)
   {
      $this->cwd = $cwd;
      $this->env = $env;
   }

   /**
    * @return string
    */
   public function getCwd(): string
   {
      return $this->cwd;
   }

   /**
    * @return array
    */
   public function getEnv(): array
   {
      return $this->env;
   }
}