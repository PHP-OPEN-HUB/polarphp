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
namespace Lit\Kernel;

/**
 * keyword: The keyword to parse for. It must end in either '.' or ':'.
 * kind: An value of ParserKind.
 * parser: A custom parser. This value may only be specified with
 * ParserKind.CUSTOM.
 *
 * Class IntegratedTestKeywordParser
 * @package Lit\Kernel
 */
class IntegratedTestKeywordParser
{
   /**
    * @var string $keyword
    */
   private $keyword;
   /**
    * @var int $kind
    */
   private $kind;
   /**
    * @var array $parsedLines
    */
   private $parsedLines;
   /**
    * @var string $value
    */
   private $value;
   /**
    * @var callable $parser
    */
   private $parser;

   public function __construct(string $keyword, int $kind, $parser = null, $initialValue = null)
   {
      $allowedSuffixes = ParserKind::allowedKeywordSuffixes($kind);
      if (strlen($keyword) == 0 || !in_array($keyword[-1], $allowedSuffixes)) {
         if (1 == count($allowedSuffixes)) {
            throw new ValueException(sprintf("Keyword '%s' of kind '%s' must end in '%s'",
               $keyword, ParserKind::getStr($kind), $allowedSuffixes[0]));
         } else {
            throw new ValueException(sprintf(
               "Keyword '%s' of kind '%s' must end in one of '%s'",
               $keyword, ParserKind::getStr($kind), join(' ', $allowedSuffixes)
            ));
         }
      }
      if ($parser != null && $kind != ParserKind::CUSTOM) {
         throw new ValueException("custom parsers can only be specified with ParserKind.CUSTOM");
      }
      $this->keyword = $keyword;
      $this->kind = $kind;
      $this->parsedLines = [];
      $this->parser = $parser;
      if ($kind == ParserKind::COMMAND) {
         $this->parser = function(int $lineNumber, string $line, array $output) use($keyword) {
            IntegratedTestKeywordParser::handleCommand($lineNumber, $line, $output);
         };
      } elseif($keyword == ParserKind::LIST) {
         $this->parser = function(int $lineNumber, string $line, array $output) use($keyword) {
            IntegratedTestKeywordParser::handleList($lineNumber, $line, $output);
         };
      } elseif($keyword == ParserKind::BOOLEAN_EXPR) {
         $this->parser = function(int $lineNumber, string $line, array $output) use($keyword) {
            IntegratedTestKeywordParser::handleBooleanExpr($lineNumber, $line, $output);
         };
      } elseif($keyword == ParserKind::TAG) {
         $this->parser = function(int $lineNumber, string $line, array $output) use($keyword) {
            IntegratedTestKeywordParser::handleTag($lineNumber, $line, $output);
         };
      } elseif($keyword == ParserKind::CUSTOM) {
         if (null == $parser) {
            throw new ValueException(sprintf("Unknown kind '%d'", $kind));
         }
      }
   }

   private function parseLine(int $lineNumber, string $line)
   {
      try {
         $this->parsedLines += [[$lineNumber, $line]];
         $this->value = $this->parser($lineNumber, $line, $this->value);
      } catch (ValueException $e) {
         throw new ValueException("%s\nin %s directive on test line %d", $e->getMessage(),
            $this->keyword, $lineNumber);
      }
   }

   /**
    * A helper for parsing TAG type keywords
    *
    * @param int $lineNumber
    * @param string $line
    * @param array $output
    */
   private static function handleTag(int $lineNumber, string $line, array $output): bool
   {
      return 0 == strlen(trim($line)) || !empty($output);
   }

   /**
    * A helper for parsing COMMAND type keywords
    *
    * @param int $lineNumber
    * @param string $line
    * @param array $output
    */
   private static function handleCommand(int $lineNumber, string $line, array $output, string $keyword): array
   {
      // Trim trailing whitespace.
      $line = rtrim($line);
      // Substitute line number expressions
      $line = str_replace('%(line)', $lineNumber, $line);
      $line = preg_replace_callback('/%\(line *([\+-]) *(\d+)\)/', function (array $matches) use ($lineNumber){
         if ($matches[1] == '+') {
            return $lineNumber + intval($matches[2]);
         }
         if ($matches[1] == '-') {
            return $lineNumber - intval($matches[2]);
         }
      }, $line);
      // Collapse lines with trailing '\\'.
      if (count($output) > 0 && $output[-1][-1] == '\\') {
         $output[-1] = substr($output[-1], 0, -1) . $line;
      } else {
         $pdbg = sprintf("%dbg(%s at line %d)", $keyword, $lineNumber);
         assert(preg_match('/%dbg\\(([^)\'"]*)\\)$/', $pdbg), "kPdbgRegex expected to match actual %dbg usage");
         $line = $pdbg . ' ' . $line;
         $output[] = $line;
      }
      return $output;
   }

   /**
    * A parser for LIST type keywords
    *
    * @param int $lineNumber
    * @param string $line
    * @param array $output
    */
   private static function handleList(int $lineNumber, string $line, array $output): array
   {
      $parts = explode(',', $line);
      foreach ($parts as $item) {
         $output[] = trim($item);
      }
      return $output;
   }

   /**
    * A parser for BOOLEAN_EXPR type keywords
    *
    * @param int $lineNumber
    * @param string $line
    * @param array $output
    */
   private static function handleBooleanExpr(int $lineNumber, string $line, array $output): array
   {
      $parts = [];
      foreach (explode(',', $line) as $item) {
         $item = trim($item);
         if (!empty($item)) {
            $parts[] = $item;
         }
      }
      if (!empty($output) && $output[-1][-1] == '\\') {
         $output[-1] = substr($output[-1], 0, -1) + $parts[0];
         unset($parts[0]);
      }
      $output += $parts;
      // Evaluate each expression to verify syntax.
      // We don't want any results, just the raised ValueError.
      foreach ($output as $item) {
         if($item != '*' && $item[-1] != '\\') {
            BooleanExpr::evaluate($item, []);
         }
      }
      return $output;
   }

   /**
    * A custom parser to transform REQUIRES-ANY: into REQUIRES:
    *
    * @param int $lineNumber
    * @param string $line
    * @param array $output
    */
   private static function handleRequiresAny(int $lineNumber, string $line, array $output): array
   {
      // Extract the conditions specified in REQUIRES-ANY: as written.
      $conditions = array();
      self::handleList($lineNumber, $line, $conditions);
      // Output a `REQUIRES: a || b || c` expression in its place.
      $expression = join(' || ', $conditions);
      self::handleBooleanExpr($lineNumber, $expression, $output);
      return $output;
   }

   /**
    * @return string
    */
   public function getKeyword(): string
   {
      return $this->keyword;
   }

   /**
    * @return ParserKind
    */
   public function getKind(): ParserKind
   {
      return $this->kind;
   }

   /**
    * @return array
    */
   public function getParsedLines(): array
   {
      return $this->parsedLines;
   }

   /**
    * @return string
    */
   public function getValue(): string
   {
      return $this->value;
   }

   /**
    * @return callable
    */
   public function getParser(): callable
   {
      return $this->parser;
   }
}