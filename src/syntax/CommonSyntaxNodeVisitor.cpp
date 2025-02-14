// This source file is part of the polarphp.org open source project
//
// Copyright (c) 2017 - 2019 polarphp software foundation
// Copyright (c) 2017 - 2019 zzu_softboy <zzu_softboy@163.com>
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://polarphp.org/LICENSE.txt for license information
// See https://polarphp.org/CONTRIBUTORS.txt for the list of polarphp project authors
//
// Created by polarboy on 2019/05/16.

#include "polarphp/syntax/SyntaxVisitor.h"

namespace polar::syntax {

void SyntaxVisitor::visit(UnknownSyntax node)
{
   visitChildren(node);
}

void SyntaxVisitor::visit(UnknownDeclSyntax node)
{
   visitChildren(node);
}

void SyntaxVisitor::visit(UnknownExprSyntax node)
{
   visitChildren(node);
}

void SyntaxVisitor::visit(UnknownStmtSyntax node)
{
   visitChildren(node);
}

} // polar::syntax
