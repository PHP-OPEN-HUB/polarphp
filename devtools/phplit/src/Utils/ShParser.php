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

use Lit\Kernel\PipelineCommand;
use Lit\Kernel\SeqCmmand;
use Lit\Kernel\ValueException;
use Lit\Kernel\ShCommand;

class ShParser
{
   /**
    * @var string $data
    */
   private $data;
   /**
    * @var bool $pipeFail
    */
   private $pipeFail;
   /**
    * @var \Generator $tokens
    */
   private $tokens;
   public function __construct($data, $win32Escapes = false, $pipeFail = false)
   {
      $this->data = $data;
      $this->pipeFail = $this->pipeFail;
      $this->tokens = new ShLexer($data, $pipeFail);
   }

   public function parse()
   {
      $lhs = $this->parsePipeline();
      while ($this->look()) {
         $operator = $this->lex();
         assert(is_array($operator) && count($operator) == 1);
         if (is_null($this->look())) {
            throw new ValueException('missing argument to operator %s', $operator[0]);
         }
         # FIXME: Operator precedence!!
         $lhs = new SeqCmmand($lhs, $operator[0], $this->parsePipeline());
      }
      return $lhs;
   }

   private function lex()
   {
      foreach ($this->tokens as $token) {
         return $token;
      }
      return null;
   }

   private function look()
   {
      return $this->tokens->current();
   }

   private function parseCommand()
   {
      $token = $this->lex();
      if (is_null($token)) {
         throw new ValueException('empty command!');
      }
      if (!is_array($token)) {
         throw new ValueException('syntax error near unexpected token %s', $token[0]);
      }
      $args = [$token];
      $redirects = [];
      while (true) {
         $token = $this->look();
         // EOF?
         if (is_null($token)) {
            break;
         }
         // If this is an argument, just add it to the current command.
         if ($token instanceof GlobItemCommand || is_string($token)) {
            $args[] = $this->lex();
            continue;
         }
         // Otherwise see if it is a terminator.
         assert(is_array($token));
         if (in_array($token[0], ['|',';','&','||','&&'])) {
            break;
         }
         // Otherwise it must be a redirection.
         $op = $this->lex();
         $arg = $this->lex();
         if (is_null($arg)) {
            throw new ValueException(sprintf('syntax error near token %s', $op[0]));
         }
         $redirects[] = [$op, $arg];
      }
      return new ShCommand($args, $redirects);
   }

   private function parsePipeline()
   {
      $negate = false;
      $commands = [$this->parseCommand()];
      while ($this->look() == ['|']) {
         $this->lex();
         $commands[] = $this->parseCommand();
      }
      return new PipelineCommand($commands, $negate, $this->pipeFail);
   }
}