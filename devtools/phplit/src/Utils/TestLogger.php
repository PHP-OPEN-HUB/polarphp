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
// Created by polarboy on 2019/10/09.

namespace Lit\Utils;

use Psr\Log\LogLevel;
use Symfony\Component\Console\Logger\ConsoleLogger;

class TestLogger
{
   /**
    * @var ConsoleLogger $logger
    */
   private static $logger;

   /**
    * @var int $numErrors
    */
   private static $numErrors = 0;

   /**
    * @var int $numWarnings
    */
   private static $numWarnings = 0;

   public static function init(ConsoleLogger $logger)
   {
      self::$logger = $logger;
   }

   public static function note(string $message): void
   {
      self::doWriteMessage(LogLevel::INFO, $message);
   }

   public static function warning(string $message): void
   {
      self::doWriteMessage(LogLevel::WARNING, $message);
      ++self::$numWarnings;
   }

   public static function error(string $message, bool $count = true): void
   {
      self::doWriteMessage(LogLevel::ERROR, $message);
      if ($count) {
         ++self::$numErrors;
      }
   }

   public static function fatal(string $message): void
   {
      self::doWriteMessage(LogLevel::EMERGENCY, $message);
      exit(2);
   }

   public static function getNumErrors(): int
   {
      return self::$numErrors;
   }

   public static function getNumWarnings(): int
   {
      return self::$numWarnings;
   }

   public static function reset()
   {
      self::$numWarnings = 0;
      self::$numErrors = 0;
   }

   private static function doWriteMessage($level, $message): void
   {
      $stack = debug_backtrace();
      $targetStack = $stack[1];
      $file = substr($targetStack['file'], strlen(LIT_ROOT_DIR) + 1);
      $location = sprintf('%s:%d', $file, $targetStack['line']);
      self::$logger->log($level, sprintf('%s: %s', $location, $message));
   }
}