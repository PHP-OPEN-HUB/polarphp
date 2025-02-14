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
// Created by polarboy on 2019/10/08.

namespace Lit;

use Symfony\Bundle\FrameworkBundle\Console\Application as BaseApplication;
use Symfony\Component\Console\Input\InputInterface;
use Symfony\Component\Console\Output\OutputInterface;
use Symfony\Component\HttpKernel\KernelInterface;

class Application extends BaseApplication
{
   const VERSION = '0.0.1';

   public function __construct(KernelInterface $Kernel)
   {
      parent::__construct($Kernel);
      $this->setName("phplit");
      $this->setVersion(Application::VERSION);
   }

   public function loadExtraFiles()
   {
      $files = array(
         "src/Utils/UtilFuncs.php"
      );
      foreach ($files as $file) {
         include LIT_ROOT_DIR .DIRECTORY_SEPARATOR . $file;
      }
   }
}