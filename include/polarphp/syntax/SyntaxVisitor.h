//===---------------- SyntaxVisitor.h - SyntaxVisitor definitions ---------===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// This source file is part of the polarphp.org open source project
//
// Copyright (c) 2017 - 2019 polarphp software foundation
// Copyright (c) 2017 - 2019 zzu_softboy <zzu_softboy@163.com>
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://polarphp.org/LICENSE.txt for license information
// See https://polarphp.org/CONTRIBUTORS.txt for the list of polarphp project authors
//
// Created by polarboy on 2019/05/08.

#ifndef POLARPHP_SYNTAX_VISITOR_H
#define POLARPHP_SYNTAX_VISITOR_H

#include "polarphp/syntax/Syntax.h"
#include "polarphp/syntax/SyntaxCollection.h"
#include "polarphp/syntax/TokenSyntax.h"
#include "polarphp/syntax/UnknownSyntax.h"
#include "polarphp/syntax/syntaxnode/CommonSyntaxNodes.h"

namespace polar::syntax {

class SyntaxVisitor
{
public:
   virtual ~SyntaxVisitor()
   {}

   virtual void visit(TokenSyntax token)
   {}

   virtual void visitPre(Syntax node)
   {}

   virtual void visitPost(Syntax node)
   {}

   virtual void visit(Syntax node);

   void visitChildren(Syntax node)
   {
      for (unsigned i = 0, e = node.getNumChildren(); i != e; ++i) {
         if (auto Child = node.getChild(i)) {
            visit(*Child);
         }
      }
   }

   /// syntax node visit methods
   virtual void visit(UnknownSyntax node);
   virtual void visit(UnknownDeclSyntax node);
   virtual void visit(UnknownExprSyntax node);
   virtual void visit(UnknownStmtSyntax node);
};

} // polar::syntax

#endif // POLARPHP_SYNTAX_VISITOR_H
