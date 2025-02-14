// This source file is part of the polarphp.org open source project
//
// Copyright (c) 2017 - 2019 polarphp software foundation
// Copyright (c) 2017 - 2019 zzu_softboy <zzu_softboy@163.com>
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://polarphp.org/LICENSE.txt for license information
// See https://polarphp.org/CONTRIBUTORS.txt for the list of polarphp project authors
//
// Created by polarboy on 2019/05/17.

#include "polarphp/syntax/syntaxnode/ExprSyntaxNodes.h"
#include "polarphp/syntax/syntaxnode/DeclSyntaxNodes.h"
#include "polarphp/syntax/syntaxnode/StmtSyntaxNodes.h"

namespace polar::syntax {

///
/// ParenDecoratedExprSyntax
///

void ParenDecoratedExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ParenDecoratedExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, LeftParenToken, std::set{TokenKindType::T_LEFT_PAREN});
   syntax_assert_child_token(raw, RightParenToken, std::set{TokenKindType::T_RIGHT_PAREN});
   syntax_assert_child_kind(raw, Expr, std::set{SyntaxKind::Expr});
#endif
}

TokenSyntax ParenDecoratedExprSyntax::getLeftParenToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftParenToken).get()};
}

ExprSyntax ParenDecoratedExprSyntax::getExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Expr).get()};
}

TokenSyntax ParenDecoratedExprSyntax::getRightParenToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightParenToken).get()};
}

ParenDecoratedExprSyntax
ParenDecoratedExprSyntax::withLeftParenToken(std::optional<TokenSyntax> leftParenToken)
{
   RefCountPtr<RawSyntax> leftParenTokenRaw;
   if (leftParenToken.has_value()) {
      leftParenTokenRaw = leftParenToken->getRaw();
   } else {
      leftParenTokenRaw = make_missing_token(T_LEFT_PAREN);
   }
   return m_data->replaceChild<ParenDecoratedExprSyntax>(leftParenTokenRaw, Cursor::LeftParenToken);
}

ParenDecoratedExprSyntax ParenDecoratedExprSyntax::withExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::UnknownExpr);
   }
   return m_data->replaceChild<ParenDecoratedExprSyntax>(exprRaw, Cursor::Expr);
}

ParenDecoratedExprSyntax
ParenDecoratedExprSyntax::withRightParenToken(std::optional<TokenSyntax> rightParenToken)
{
   RefCountPtr<RawSyntax> rightParenTokenRaw;
   if (rightParenToken.has_value()) {
      rightParenTokenRaw = rightParenToken->getRaw();
   } else {
      rightParenTokenRaw = make_missing_token(T_LEFT_PAREN);
   }
   return m_data->replaceChild<ParenDecoratedExprSyntax>(rightParenTokenRaw, Cursor::RightParenToken);
}

///
/// NullExprSyntax
///
void NullExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == NullExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, NullKeyword, std::set{TokenKindType::T_NULL});
#endif
}

TokenSyntax NullExprSyntax::getNullKeyword()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::NullKeyword).get()};
}

NullExprSyntax NullExprSyntax::withNullKeyword(std::optional<TokenSyntax> keyword)
{
   RefCountPtr<RawSyntax> rawKeyword;
   if (keyword.has_value()) {
      rawKeyword = keyword->getRaw();
   } else {
      rawKeyword = RawSyntax::missing(TokenKindType::T_NULL,
                                      OwnedString::makeUnowned((get_token_text(TokenKindType::T_NULL))));
   }
   return m_data->replaceChild<NullExprSyntax>(rawKeyword, Cursor::NullKeyword);
}

///
/// OptionalExprSyntax
///
void OptionalExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == OptionalExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Expr, std::set{SyntaxKind::Expr});
#endif
}

std::optional<ExprSyntax> OptionalExprSyntax::getExpr()
{
   RefCountPtr<SyntaxData> exprData = m_data->getChild(Cursor::Expr);
   if (!exprData) {
      return std::nullopt;
   }
   return ExprSyntax {m_root, exprData.get()};
}

OptionalExprSyntax OptionalExprSyntax::withExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<OptionalExprSyntax>(exprRaw, Cursor::Expr);
}

///
/// ExprListItemSyntax
///
void ExprListItemSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ExprListItemSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Expr, std::set{SyntaxKind::Expr});
   syntax_assert_child_token(raw, Comma, std::set{TokenKindType::T_COMMA});
#endif
}

std::optional<TokenSyntax> ExprListItemSyntax::getComma()
{
   RefCountPtr<SyntaxData> commaData = m_data->getChild(Cursor::Comma);
   if (!commaData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, commaData.get()};
}

ExprSyntax ExprListItemSyntax::getExpr()
{
   return ExprSyntax{m_root, m_data->getChild(Cursor::Expr).get()};
}

ExprListItemSyntax ExprListItemSyntax::withExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<ExprListItemSyntax>(exprRaw, Cursor::Expr);
}

ExprListItemSyntax ExprListItemSyntax::withComma(std::optional<TokenSyntax> comma)
{
   RefCountPtr<RawSyntax> trailingCommaRaw;
   if (comma.has_value()) {
      trailingCommaRaw = comma->getRaw();
   } else {
      trailingCommaRaw = nullptr;
   }
   return m_data->replaceChild<ExprListItemSyntax>(trailingCommaRaw, Cursor::Comma);
}

///
/// VariableExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType VariableExprSyntax::CHILD_NODE_CHOICES
{
   {
      VariableExprSyntax::Var, {
         SyntaxKind::CallableVariableExpr, SyntaxKind::StaticPropertyExpr,
               SyntaxKind::InstancePropertyExpr
      }
   }
};
#endif

void VariableExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == VariableExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Var, CHILD_NODE_CHOICES.at(Cursor::Var));
#endif
}

ExprSyntax VariableExprSyntax::getVar()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Var).get()};
}

VariableExprSyntax VariableExprSyntax::withVar(std::optional<ExprSyntax> var)
{
   RefCountPtr<RawSyntax> varRaw;
   if (var.has_value()) {
      varRaw = var->getRaw();
   } else {
      varRaw = RawSyntax::missing(SyntaxKind::UnknownExpr);
   }
   return m_data->replaceChild<VariableExprSyntax>(varRaw, Cursor::Var);
}

///
/// ReferencedVariableExprSyntax
///
void ReferencedVariableExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ReferencedVariableExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, RefToken, std::set{TokenKindType::T_AMPERSAND});
   syntax_assert_child_kind(raw, VariableExpr, std::set{SyntaxKind::VariableExpr});
#endif
}

TokenSyntax ReferencedVariableExprSyntax::getRefToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RefToken).get()};
}

VariableExprSyntax ReferencedVariableExprSyntax::getVariableExpr()
{
   return VariableExprSyntax {m_root, m_data->getChild(Cursor::VariableExpr).get()};
}

ReferencedVariableExprSyntax
ReferencedVariableExprSyntax::withRefToken(std::optional<TokenSyntax> refToken)
{
   RefCountPtr<RawSyntax> rawRefToken;
   if (refToken.has_value()) {
      rawRefToken = refToken->getRaw();
   } else {
      rawRefToken = make_missing_token(T_AMPERSAND);
   }
   return m_data->replaceChild<ReferencedVariableExprSyntax>(rawRefToken, Cursor::RefToken);
}

ReferencedVariableExprSyntax
ReferencedVariableExprSyntax::withVariableExpr(std::optional<VariableExprSyntax> valueExpr)
{
   RefCountPtr<RawSyntax> rawValueExpr;
   if (valueExpr.has_value()) {
      rawValueExpr = valueExpr->getRaw();
   } else {
      rawValueExpr = RawSyntax::missing(SyntaxKind::VariableExpr);
   }
   return m_data->replaceChild<ReferencedVariableExprSyntax>(rawValueExpr, Cursor::VariableExpr);
}

///
/// ClassConstIdentifierExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType ClassConstIdentifierExprSyntax::CHILD_NODE_CHOICES
{
   {
      ClassConstIdentifierExprSyntax::ClassName, {
         SyntaxKind::VariableClassNameClause, SyntaxKind::ClassNameClause
      }
   }
};
#endif

void ClassConstIdentifierExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ClassConstIdentifierExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, ClassName, CHILD_NODE_CHOICES.at(Cursor::ClassName));
   syntax_assert_child_token(raw, SeparatorToken, std::set{TokenKindType::T_PAAMAYIM_NEKUDOTAYIM});
   syntax_assert_child_kind(raw, Identifier, std::set{SyntaxKind::Identifier});
#endif
}

Syntax ClassConstIdentifierExprSyntax::getClassName()
{
   return Syntax {m_root, m_data->getChild(Cursor::ClassName).get()};
}

TokenSyntax ClassConstIdentifierExprSyntax::getSeparatorToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::SeparatorToken).get()};
}

IdentifierSyntax ClassConstIdentifierExprSyntax::getIdentifier()
{
   return IdentifierSyntax {m_root, m_data->getChild(Cursor::Identifier).get()};
}

ClassConstIdentifierExprSyntax ClassConstIdentifierExprSyntax::withClassName(std::optional<Syntax> className)
{
   RefCountPtr<RawSyntax> classNameRaw;
   if (className.has_value()) {
      classNameRaw = className->getRaw();
   } else {
      classNameRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<ClassConstIdentifierExprSyntax>(classNameRaw, Cursor::ClassName);
}

ClassConstIdentifierExprSyntax ClassConstIdentifierExprSyntax::withSeparatorToken(std::optional<TokenSyntax> separator)
{
   RefCountPtr<RawSyntax> separatorRaw;
   if (separator.has_value()) {
      separatorRaw = separator->getRaw();
   } else {
      separatorRaw = make_missing_token(T_PAAMAYIM_NEKUDOTAYIM);
   }
   return m_data->replaceChild<ClassConstIdentifierExprSyntax>(separatorRaw, Cursor::SeparatorToken);
}

ClassConstIdentifierExprSyntax ClassConstIdentifierExprSyntax::withIdentifier(std::optional<TokenSyntax> identifier)
{
   RefCountPtr<RawSyntax> identifierRaw;
   if (identifier.has_value()) {
      identifierRaw = identifier->getRaw();
   } else {
      identifierRaw = RawSyntax::missing(SyntaxKind::Identifier);
   }
   return m_data->replaceChild<ClassConstIdentifierExprSyntax>(identifierRaw, Cursor::Identifier);
}

///
/// ConstExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType ConstExprSyntax::CHILD_NODE_CHOICES
{
   {
      ConstExprSyntax::Identifier, {
         SyntaxKind::Name, SyntaxKind::ClassConstIdentifierExpr
      }
   }
};
#endif

void ConstExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ConstExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Identifier, CHILD_NODE_CHOICES.at(Cursor::Identifier));
#endif
}

Syntax ConstExprSyntax::getIdentifier()
{
   return Syntax {m_root, m_data->getChild(Cursor::Identifier).get()};
}

ConstExprSyntax ConstExprSyntax::withIdentifier(std::optional<Syntax> identifier)
{
   RefCountPtr<RawSyntax> identifierRaw;
   if (identifier.has_value()) {
      identifierRaw = identifier->getRaw();
   } else {
      identifierRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<ConstExprSyntax>(identifierRaw, Cursor::Identifier);
}

///
/// NewVariableClauseSyntax
///

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType NewVariableClauseSyntax::CHILD_NODE_CHOICES
{
   {
      NewVariableClauseSyntax::VarNode, {
         SyntaxKind::SimpleVariableExpr, SyntaxKind::ArrayAccessExpr,
               SyntaxKind::BraceDecoratedArrayAccessExpr, SyntaxKind::InstancePropertyExpr,
               SyntaxKind::StaticPropertyExpr,
      }
   }
};
#endif

void NewVariableClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == NewVariableClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, VarNode, CHILD_NODE_CHOICES.at(Cursor::VarNode));
#endif
}

ExprSyntax NewVariableClauseSyntax::getVar()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::VarNode).get()};
}

NewVariableClauseSyntax NewVariableClauseSyntax::withVar(std::optional<ExprSyntax> var)
{
   RefCountPtr<RawSyntax> varRaw;
   if (var.has_value()) {
      varRaw = var->getRaw();
   } else {
      varRaw = RawSyntax::missing(SyntaxKind::UnknownExpr);
   }
   return m_data->replaceChild<NewVariableClauseSyntax>(varRaw, Cursor::VarNode);
}

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType CallableVariableExprSyntax::CHILD_NODE_CHOICES
{
   {
      CallableVariableExprSyntax::Var, {
         SyntaxKind::SimpleVariableExpr, SyntaxKind::ArrayAccessExpr,
               SyntaxKind::BraceDecoratedArrayAccessExpr, SyntaxKind::InstanceMethodCallExpr,
               SyntaxKind::FunctionCallExpr
      }
   }
};
#endif

void CallableVariableExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == CallableVariableExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Var, CHILD_NODE_CHOICES.at(Cursor::Var));
#endif
}

ExprSyntax CallableVariableExprSyntax::getVar()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Var).get()};
}

CallableVariableExprSyntax CallableVariableExprSyntax::withVar(std::optional<ExprSyntax> var)
{
   RefCountPtr<RawSyntax> varRaw;
   if (var.has_value()) {
      varRaw = var->getRaw();
   } else {
      varRaw = RawSyntax::missing(SyntaxKind::UnknownExpr);
   }
   return m_data->replaceChild<CallableVariableExprSyntax>(varRaw, Cursor::Var);
}

///
/// CallableFuncNameClauseSyntax
///

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType CallableFuncNameClauseSyntax::CHILD_NODE_CHOICES
{
   {
      CallableFuncNameClauseSyntax::FuncName, {
         SyntaxKind::CallableVariableExpr, SyntaxKind::ParenDecoratedExpr,
               SyntaxKind::DereferencableScalarExpr,
      }
   }
};
#endif

void CallableFuncNameClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == CallableFuncNameClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, FuncName, CHILD_NODE_CHOICES.at(Cursor::FuncName));
#endif
}

Syntax CallableFuncNameClauseSyntax::getFuncName()
{
   return Syntax {m_root, m_data->getChild(Cursor::FuncName).get()};
}

CallableFuncNameClauseSyntax CallableFuncNameClauseSyntax::withFuncName(std::optional<Syntax> funcName)
{
   RefCountPtr<RawSyntax> funcNameRaw;
   if (funcName.has_value()) {
      funcNameRaw = funcName->getRaw();
   } else {
      funcNameRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<CallableFuncNameClauseSyntax>(funcNameRaw, Cursor::FuncName);
}

///
/// MemberNameClauseSyntax
///

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType MemberNameClauseSyntax::CHILD_NODE_CHOICES
{
   {
      MemberNameClauseSyntax::Name, {
         SyntaxKind::Identifier,  SyntaxKind::BraceDecoratedExprClause,
               SyntaxKind::SimpleVariableExpr
      }
   }
};
#endif

void MemberNameClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == MemberNameClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Name, CHILD_NODE_CHOICES.at(Cursor::Name));
#endif
}

Syntax MemberNameClauseSyntax::getName()
{
   return Syntax {m_root, m_data->getChild(Cursor::Name).get()};
}

MemberNameClauseSyntax MemberNameClauseSyntax::withName(std::optional<Syntax> name)
{
   RefCountPtr<RawSyntax> nameRaw;
   if (name.has_value()) {
      nameRaw = name->getRaw();
   } else {
      nameRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<MemberNameClauseSyntax>(nameRaw, Cursor::Name);
}

///
/// PropertyNameClauseSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType PropertyNameClauseSyntax::CHILD_NODE_CHOICES
{
   {
      PropertyNameClauseSyntax::Name, {
         SyntaxKind::BraceDecoratedExprClause, SyntaxKind::SimpleVariableExpr
      }
   }
};
#endif

void PropertyNameClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ConstExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Name, CHILD_NODE_CHOICES.at(Cursor::Name));
#endif
}

Syntax PropertyNameClauseSyntax::getName()
{
   return Syntax {m_root, m_data->getChild(Cursor::Name).get()};
}

PropertyNameClauseSyntax PropertyNameClauseSyntax::withName(std::optional<Syntax> name)
{
   RefCountPtr<RawSyntax> nameRaw;
   if (name.has_value()) {
      nameRaw = name->getRaw();
   } else {
      nameRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<PropertyNameClauseSyntax>(nameRaw, Cursor::Name);
}

///
/// InstancePropertyExprSyntax
///

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType InstancePropertyExprSyntax::CHILD_NODE_CHOICES
{
   {
      InstancePropertyExprSyntax::ObjectRef, {
         SyntaxKind::NewVariableClause, SyntaxKind::DereferencableClause
      }
   }
};
#endif

void InstancePropertyExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == InstancePropertyExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, ObjectRef, CHILD_NODE_CHOICES.at(Cursor::ObjectRef));
   syntax_assert_child_token(raw, Separator, std::set{TokenKindType::T_OBJECT_OPERATOR});
   if (const RefCountPtr<RawSyntax> &propertyChild = raw->getChild(Cursor::PropertyName)) {
      if (propertyChild->isToken()) {
         syntax_assert_child_token(raw, PropertyName, std::set{TokenKindType::T_IDENTIFIER_STRING});
      } else {
         syntax_assert_child_kind(raw, PropertyName, std::set{SyntaxKind::PropertyNameClause});
      }
   }
#endif
}

Syntax InstancePropertyExprSyntax::getObjectRef()
{
   return Syntax {m_root, m_data->getChild(Cursor::ObjectRef).get()};
}

TokenSyntax InstancePropertyExprSyntax::getSeparator()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Separator).get()};
}

Syntax InstancePropertyExprSyntax::getPropertyName()
{
   return Syntax {m_root, m_data->getChild(Cursor::PropertyName).get()};
}

InstancePropertyExprSyntax
InstancePropertyExprSyntax::withObjectRef(std::optional<Syntax> objectRef)
{
   RefCountPtr<RawSyntax> objectRefRaw;
   if (objectRef.has_value()) {
      objectRefRaw = objectRef->getRaw();
   } else {
      objectRefRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<InstancePropertyExprSyntax>(objectRefRaw, Cursor::ObjectRef);
}

InstancePropertyExprSyntax
InstancePropertyExprSyntax::withSeparator(std::optional<TokenSyntax> separator)
{
   RefCountPtr<RawSyntax> separatorRaw;
   if (separator.has_value()) {
      separatorRaw = separator->getRaw();
   } else {
      separatorRaw = make_missing_token(T_OBJECT_OPERATOR);
   }
   return m_data->replaceChild<InstancePropertyExprSyntax>(separatorRaw, Cursor::Separator);
}

InstancePropertyExprSyntax
InstancePropertyExprSyntax::withPropertyName(std::optional<Syntax> propertyName)
{
   RefCountPtr<RawSyntax> propertyNameRaw;
   if (propertyName.has_value()) {
      propertyNameRaw = propertyName->getRaw();
   } else {
      propertyNameRaw = RawSyntax::missing(SyntaxKind::PropertyNameClause);
   }
   return m_data->replaceChild<InstancePropertyExprSyntax>(propertyNameRaw, Cursor::PropertyName);
}

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType StaticPropertyExprSyntax::CHILD_NODE_CHOICES
{
   {
      StaticPropertyExprSyntax::ClassName, {
         SyntaxKind::ClassNameClause, SyntaxKind::VariableClassNameClause,
               SyntaxKind::NewVariableClause
      }
   }
};
#endif

void StaticPropertyExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == StaticPropertyExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, ClassName, CHILD_NODE_CHOICES.at(Cursor::ClassName));
   syntax_assert_child_token(raw, Separator, std::set{TokenKindType::T_OBJECT_OPERATOR});
   syntax_assert_child_kind(raw, MemberName, std::set{SyntaxKind::SimpleVariableExpr});
#endif
}

Syntax StaticPropertyExprSyntax::getClassName()
{
   return Syntax {m_root, m_data->getChild(Cursor::ClassName).get()};
}

TokenSyntax StaticPropertyExprSyntax::getSeparator()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Separator).get()};
}

SimpleVariableExprSyntax StaticPropertyExprSyntax::getMemberName()
{
   return SimpleVariableExprSyntax {m_root, m_data->getChild(Cursor::MemberName).get()};
}

StaticPropertyExprSyntax StaticPropertyExprSyntax::withClassName(std::optional<Syntax> className)
{
   RefCountPtr<RawSyntax> classNameRaw;
   if (className.has_value()) {
      classNameRaw = className->getRaw();
   } else {
      classNameRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<StaticPropertyExprSyntax>(classNameRaw, Cursor::ClassName);
}

StaticPropertyExprSyntax StaticPropertyExprSyntax::withSeparator(std::optional<TokenSyntax> separator)
{
   RefCountPtr<RawSyntax> separatorRaw;
   if (separator.has_value()) {
      separatorRaw = separator->getRaw();
   } else {
      separatorRaw = make_missing_token(T_PAAMAYIM_NEKUDOTAYIM);
   }
   return m_data->replaceChild<StaticPropertyExprSyntax>(separatorRaw, Cursor::Separator);
}

StaticPropertyExprSyntax
StaticPropertyExprSyntax::withMemberName(std::optional<SimpleVariableExprSyntax> memberName)
{
   RefCountPtr<RawSyntax> memberNameRaw;
   if (memberName.has_value()) {
      memberNameRaw = memberName->getRaw();
   } else {
      memberNameRaw = RawSyntax::missing(SyntaxKind::SimpleVariableExpr);
   }
   return m_data->replaceChild<StaticPropertyExprSyntax>(memberNameRaw, Cursor::MemberName);
}

///
/// ArgumentSyntax
///
void ArgumentSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ArgumentSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, EllipsisToken, std::set{TokenKindType::T_ELLIPSIS});
   syntax_assert_child_kind(raw, Expr, std::set{SyntaxKind::Expr});
#endif
}

std::optional<TokenSyntax> ArgumentSyntax::getEllipsisToken()
{
   RefCountPtr<SyntaxData> ellipsisTokenData = m_data->getChild(Cursor::EllipsisToken);
   if (!ellipsisTokenData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, ellipsisTokenData.get()};
}

ExprSyntax ArgumentSyntax::getExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Expr).get()};
}

ArgumentSyntax ArgumentSyntax::withEllipsisToken(std::optional<TokenSyntax> ellipsisToken)
{
   RefCountPtr<RawSyntax> ellipsisTokenRaw;
   if (ellipsisToken.has_value()) {
      ellipsisTokenRaw = ellipsisToken->getRaw();
   } else {
      ellipsisTokenRaw = nullptr;
   }
   return m_data->replaceChild<ArgumentSyntax>(ellipsisTokenRaw, Cursor::EllipsisToken);
}

ArgumentSyntax ArgumentSyntax::withExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<ArgumentSyntax>(exprRaw, Cursor::Expr);
}

///
/// ArgumentListItemSyntax
///
void ArgumentListItemSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ArgumentListItemSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, Comma, std::set{TokenKindType::T_COMMA});
   syntax_assert_child_kind(raw, Argument, std::set{SyntaxKind::Argument});
#endif
}

std::optional<TokenSyntax> ArgumentListItemSyntax::getComma()
{
   RefCountPtr<SyntaxData> tokenSyntaxData = m_data->getChild(Cursor::Argument);
   if (!tokenSyntaxData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, tokenSyntaxData.get()};
}

ArgumentSyntax ArgumentListItemSyntax::getArgument()
{
   return ArgumentSyntax {m_root, m_data->getChild(Cursor::Argument).get()};
}

ArgumentListItemSyntax ArgumentListItemSyntax::withComma(std::optional<TokenSyntax> comma)
{
   RefCountPtr<RawSyntax> commaRaw;
   if (comma.has_value()) {
      commaRaw = comma->getRaw();
   } else {
      commaRaw = nullptr;
   }
   return m_data->replaceChild<ArgumentListItemSyntax>(commaRaw, Cursor::Comma);
}

ArgumentListItemSyntax ArgumentListItemSyntax::withArgument(std::optional<ArgumentSyntax> argument)
{
   RefCountPtr<RawSyntax> argumentRaw;
   if (argument.has_value()) {
      argumentRaw = argument->getRaw();
   } else {
      argumentRaw = RawSyntax::missing(SyntaxKind::Argument);
   }
   return m_data->replaceChild<ArgumentListItemSyntax>(argumentRaw, Cursor::Argument);
}

///
/// ArgumentListClauseSyntax
///
void ArgumentListClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ArgumentListClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, LeftParenToken, std::set{TokenKindType::T_LEFT_PAREN});
   syntax_assert_child_kind(raw, Arguments, std::set{SyntaxKind::ArgumentList});
   syntax_assert_child_token(raw, RightParenToken, std::set{TokenKindType::T_RIGHT_PAREN});
#endif
}

TokenSyntax ArgumentListClauseSyntax::getLeftParenToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftParenToken).get()};
}

std::optional<ArgumentListSyntax> ArgumentListClauseSyntax::getArguments()
{
   RefCountPtr<SyntaxData> argumentsData = m_data->getChild(Cursor::Arguments);
   if (!argumentsData) {
      return std::nullopt;
   }
   return ArgumentListSyntax {m_root, argumentsData.get()};
}

TokenSyntax ArgumentListClauseSyntax::getRightParenToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightParenToken).get()};
}

ArgumentListClauseSyntax ArgumentListClauseSyntax::withLeftParenToken(std::optional<TokenSyntax> leftParenToken)
{
   RefCountPtr<RawSyntax> leftParenTokenRaw;
   if (leftParenToken.has_value()) {
      leftParenTokenRaw = leftParenToken->getRaw();
   } else {
      leftParenTokenRaw = make_missing_token(T_LEFT_PAREN);
   }
   return m_data->replaceChild<ArgumentListClauseSyntax>(leftParenTokenRaw, Cursor::LeftParenToken);
}

ArgumentListClauseSyntax ArgumentListClauseSyntax::withArguments(std::optional<ArgumentListSyntax> arguments)
{
   RefCountPtr<RawSyntax> argumentsRaw;
   if (arguments.has_value()) {
      argumentsRaw = arguments->getRaw();
   } else {
      argumentsRaw = nullptr;
   }
   return m_data->replaceChild<ArgumentListClauseSyntax>(argumentsRaw, Cursor::Arguments);
}

ArgumentListClauseSyntax ArgumentListClauseSyntax::withRightParenToken(std::optional<TokenSyntax> rightParenToken)
{
   RefCountPtr<RawSyntax> rightParenTokenRaw;
   if (rightParenToken.has_value()) {
      rightParenTokenRaw = rightParenToken->getRaw();
   } else {
      rightParenTokenRaw = make_missing_token(T_RIGHT_PAREN);
   }
   return m_data->replaceChild<ArgumentListClauseSyntax>(rightParenTokenRaw, Cursor::RightParenToken);
}

///
/// DereferencableClauseSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType DereferencableClauseSyntax::CHILD_NODE_CHOICES
{
   {
      DereferencableClauseSyntax::DereferencableExpr, {
         SyntaxKind::VariableExpr, SyntaxKind::ParenDecoratedExpr,
               SyntaxKind::DereferencableScalarExpr
      }
   }
};
#endif

void DereferencableClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == DereferencableClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, DereferencableExpr, CHILD_NODE_CHOICES.at(Cursor::DereferencableExpr));
#endif
}

ExprSyntax DereferencableClauseSyntax::getDereferencableExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::DereferencableExpr).get()};
}

DereferencableClauseSyntax
DereferencableClauseSyntax::withDereferencableExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::UnknownExpr);
   }
   return m_data->replaceChild<DereferencableClauseSyntax>(exprRaw, Cursor::DereferencableExpr);
}

///
/// VariableClassNameClauseSyntax
///
void VariableClassNameClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == VariableClassNameClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, DereferencableExpr, std::set{SyntaxKind::DereferencableClause});
#endif
}

DereferencableClauseSyntax VariableClassNameClauseSyntax::getDereferencableExpr()
{
   return DereferencableClauseSyntax {m_root, m_data->getChild(Cursor::DereferencableExpr).get()};
}

VariableClassNameClauseSyntax
VariableClassNameClauseSyntax::withDereferencableExpr(std::optional<DereferencableClauseSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::DereferencableClause);
   }
   return m_data->replaceChild<VariableClassNameClauseSyntax>(exprRaw, Cursor::DereferencableExpr);
}

///
/// ClassNameClauseSyntax
///
void ClassNameClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ClassNameClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Name, std::set{SyntaxKind::Name});
   syntax_assert_child_token(raw, Name, std::set{TokenKindType::T_STATIC});
#endif
}

Syntax ClassNameClauseSyntax::getName()
{
   return Syntax {m_root, m_data->getChild(Cursor::Name).get()};
}

ClassNameClauseSyntax ClassNameClauseSyntax::withName(std::optional<Syntax> name)
{
   RefCountPtr<RawSyntax> nameRaw;
   if (name.has_value()) {
      nameRaw = name->getRaw();
   } else {
      nameRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<ClassNameClauseSyntax>(nameRaw, Cursor::Name);
}

///
/// ClassNameRefClauseSyntax
///

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType ClassNameRefClauseSyntax::CHILD_NODE_CHOICES
{
   {
      ClassNameRefClauseSyntax::Name, {
         SyntaxKind::ClassNameClause, SyntaxKind::NewVariableClause,
      }
   }
};
#endif

void ClassNameRefClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ClassNameRefClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Name, CHILD_NODE_CHOICES.at(Cursor::Name));
#endif
}

Syntax ClassNameRefClauseSyntax::getName()
{
   return Syntax {m_root, m_data->getChild(Cursor::Name).get()};
}

ClassNameRefClauseSyntax ClassNameRefClauseSyntax::withName(std::optional<Syntax> name)
{
   RefCountPtr<RawSyntax> nameRaw;
   if (name.has_value()) {
      nameRaw = name->getRaw();
   } else {
      nameRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<ClassNameRefClauseSyntax>(nameRaw, Cursor::Name);
}

///
/// BraceDecoratedExprClauseSyntax
///
void BraceDecoratedExprClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == BraceDecoratedExprClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, LeftBrace, std::set{TokenKindType::T_LEFT_BRACE});
   syntax_assert_child_token(raw, RightBrace, std::set{TokenKindType::T_RIGHT_BRACE});
   if (const RefCountPtr<RawSyntax> &exprChild = raw->getChild(Cursor::Expr)) {
      assert(exprChild->kindOf(SyntaxKind::Expr));
   }
#endif
}

TokenSyntax BraceDecoratedExprClauseSyntax::getLeftBrace()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftBrace).get()};
}

ExprSyntax BraceDecoratedExprClauseSyntax::getExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Expr).get()};
}

TokenSyntax BraceDecoratedExprClauseSyntax::getRightBrace()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightBrace).get()};
}

BraceDecoratedExprClauseSyntax BraceDecoratedExprClauseSyntax::withLeftBrace(std::optional<TokenSyntax> leftBrace)
{
   RefCountPtr<RawSyntax> leftBraceRaw;
   if (leftBrace.has_value()) {
      leftBraceRaw = leftBrace->getRaw();
   } else {
      leftBraceRaw = RawSyntax::missing(TokenKindType::T_LEFT_BRACE,
                                        OwnedString::makeUnowned(get_token_text(TokenKindType::T_LEFT_BRACE)));
   }
   return m_data->replaceChild<BraceDecoratedExprClauseSyntax>(leftBraceRaw, Cursor::LeftBrace);
}

BraceDecoratedExprClauseSyntax BraceDecoratedExprClauseSyntax::withExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::UnknownExpr);
   }
   return m_data->replaceChild<BraceDecoratedExprClauseSyntax>(exprRaw, Cursor::Expr);
}

BraceDecoratedExprClauseSyntax BraceDecoratedExprClauseSyntax::withRightBrace(std::optional<TokenSyntax> rightBrace)
{
   RefCountPtr<RawSyntax> rightBraceRaw;
   if (rightBrace.has_value()) {
      rightBraceRaw = rightBrace->getRaw();
   } else {
      rightBraceRaw = RawSyntax::missing(TokenKindType::T_RIGHT_BRACE,
                                         OwnedString::makeUnowned(get_token_text(TokenKindType::T_RIGHT_BRACE)));
   }
   return m_data->replaceChild<BraceDecoratedExprClauseSyntax>(rightBraceRaw, Cursor::RightBrace);
}

///
/// BraceDecoratedVariableExprSyntax
///
void BraceDecoratedVariableExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == BraceDecoratedVariableExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, DollarSign, std::set{TokenKindType::T_DOLLAR_SIGN});
   if (const RefCountPtr<RawSyntax> &exprChild = raw->getChild(Cursor::DecoratedExpr)) {
      assert(exprChild->kindOf(SyntaxKind::BraceDecoratedExprClause));
   }
#endif
}

TokenSyntax BraceDecoratedVariableExprSyntax::getDollarSign()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::DollarSign).get()};
}

BraceDecoratedExprClauseSyntax BraceDecoratedVariableExprSyntax::getDecoratedExpr()
{
   return BraceDecoratedExprClauseSyntax{m_root, m_data->getChild(Cursor::DecoratedExpr).get()};
}

BraceDecoratedVariableExprSyntax
BraceDecoratedVariableExprSyntax::withDollarSign(std::optional<TokenSyntax> dollarSign)
{
   RefCountPtr<RawSyntax> dollarSignRaw;
   if (dollarSign.has_value()) {
      dollarSignRaw = dollarSign->getRaw();
   } else {
      dollarSignRaw = RawSyntax::missing(TokenKindType::T_DOLLAR_SIGN,
                                         OwnedString::makeUnowned(get_token_text(TokenKindType::T_DOLLAR_SIGN)));
   }
   return m_data->replaceChild<BraceDecoratedVariableExprSyntax>(dollarSignRaw, Cursor::DollarSign);
}

BraceDecoratedVariableExprSyntax
BraceDecoratedVariableExprSyntax::withDecoratedExpr(std::optional<BraceDecoratedExprClauseSyntax> decoratedExpr)
{
   RefCountPtr<RawSyntax> decoratedExprRaw;
   if (decoratedExpr.has_value()) {
      decoratedExprRaw = decoratedExpr->getRaw();
   } else {
      decoratedExprRaw = RawSyntax::missing(SyntaxKind::BraceDecoratedExprClause);
   }
   return m_data->replaceChild<BraceDecoratedVariableExprSyntax>(decoratedExprRaw, Cursor::DecoratedExpr);
}

///
/// ArrayKeyValuePairItemSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType ArrayKeyValuePairItemSyntax::CHILD_NODE_CHOICES
{
   {
      ArrayKeyValuePairItemSyntax::Value, {
         SyntaxKind::ReferencedVariableExpr, SyntaxKind::VariableExpr
      }
   }
};
#endif

void ArrayKeyValuePairItemSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ArrayKeyValuePairItemSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, KeyExpr, std::set{TokenKindType::T_DOUBLE_ARROW});
   syntax_assert_child_token(raw, DoubleArrowToken, std::set{TokenKindType::T_DOUBLE_ARROW});
   syntax_assert_child_kind(raw, Value, CHILD_NODE_CHOICES.at(Cursor::Value));
#endif
}

std::optional<ExprSyntax> ArrayKeyValuePairItemSyntax::getKeyExpr()
{
   RefCountPtr<SyntaxData> keyExprData = m_data->getChild(Cursor::KeyExpr);
   if (!keyExprData) {
      return std::nullopt;
   }
   return ExprSyntax {m_root, keyExprData.get()};
}

std::optional<TokenSyntax> ArrayKeyValuePairItemSyntax::getDoubleArrowToken()
{
   RefCountPtr<SyntaxData> doubleArrowTokenData = m_data->getChild(Cursor::DoubleArrowToken);
   if (!doubleArrowTokenData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, doubleArrowTokenData.get()};
}

ExprSyntax ArrayKeyValuePairItemSyntax::getValue()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Value).get()};
}

ArrayKeyValuePairItemSyntax ArrayKeyValuePairItemSyntax::withKeyExpr(std::optional<ExprSyntax> keyExpr)
{
   RefCountPtr<RawSyntax> keyExprRaw;
   if (keyExpr.has_value()) {
      keyExprRaw = keyExpr->getRaw();
   } else {
      keyExprRaw = nullptr;
   }
   return m_data->replaceChild<ArrayKeyValuePairItemSyntax>(keyExprRaw, Cursor::KeyExpr);
}

ArrayKeyValuePairItemSyntax ArrayKeyValuePairItemSyntax::withDoubleArrowToken(std::optional<TokenSyntax> doubleArrowToken)
{
   RefCountPtr<RawSyntax> doubleArrowTokenRaw;
   if (doubleArrowToken.has_value()) {
      doubleArrowTokenRaw = doubleArrowToken->getRaw();
   } else {
      doubleArrowTokenRaw = nullptr;
   }
   return m_data->replaceChild<ArrayKeyValuePairItemSyntax>(doubleArrowTokenRaw, Cursor::DoubleArrowToken);
}

ArrayKeyValuePairItemSyntax ArrayKeyValuePairItemSyntax::withValue(std::optional<ExprSyntax> value)
{
   RefCountPtr<RawSyntax> valueRaw;
   if (value.has_value()) {
      valueRaw = value->getRaw();
   } else {
      valueRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<ArrayKeyValuePairItemSyntax>(valueRaw, Cursor::Value);
}

///
/// ArrayUnpackPairItemSyntax
///
void ArrayUnpackPairItemSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ArrayUnpackPairItemSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, EllipsisToken, std::set{TokenKindType::T_ELLIPSIS});
   syntax_assert_child_kind(raw, UnpackExpr, std::set{SyntaxKind::Expr});
#endif
}

TokenSyntax ArrayUnpackPairItemSyntax::getEllipsisToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::EllipsisToken).get()};
}

ExprSyntax ArrayUnpackPairItemSyntax::getUnpackExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::UnpackExpr).get()};
}

ArrayUnpackPairItemSyntax ArrayUnpackPairItemSyntax::withEllipsisToken(std::optional<TokenSyntax> ellipsisToken)
{
   RefCountPtr<RawSyntax> ellipsisTokenRaw;
   if (ellipsisToken.has_value()) {
      ellipsisTokenRaw = ellipsisToken->getRaw();
   } else {
      ellipsisTokenRaw = RawSyntax::missing(TokenKindType::T_ELLIPSIS,
                                            OwnedString::makeUnowned(get_token_text(TokenKindType::T_ELLIPSIS)));
   }
   return m_data->replaceChild<ArrayUnpackPairItemSyntax>(ellipsisTokenRaw, Cursor::EllipsisToken);
}

ArrayUnpackPairItemSyntax ArrayUnpackPairItemSyntax::withUnpackExpr(std::optional<ExprSyntax> unpackExpr)
{
   RefCountPtr<RawSyntax> unpackExprRaw;
   if (unpackExpr.has_value()) {
      unpackExprRaw = unpackExpr->getRaw();
   } else {
      unpackExprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<ArrayUnpackPairItemSyntax>(unpackExprRaw, Cursor::UnpackExpr);
}

///
/// ArrayPairSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType ArrayPairSyntax::CHILD_NODE_CHOICES
{
   {
      ArrayPairSyntax::Item, {
         SyntaxKind::ArrayKeyValuePairItem,
               SyntaxKind::ArrayUnpackPairItem
      }
   }
};
#endif

void ArrayPairSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ArrayPairSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Item, CHILD_NODE_CHOICES.at(Cursor::Item));
#endif
}

Syntax ArrayPairSyntax::getItem()
{
   return Syntax {m_root, m_data->getChild(Cursor::Item).get()};
}

ArrayPairSyntax ArrayPairSyntax::withItem(std::optional<Syntax> item)
{
   RefCountPtr<RawSyntax> itemRaw;
   if (item.has_value()) {
      itemRaw = item->getRaw();
   } else {
      itemRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<ArrayPairSyntax>(itemRaw, Cursor::Item);
}

///
/// ArrayPairListItemSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType ArrayPairListItemSyntax::CHILD_NODE_CHOICES
{
   {
      Cursor::ArrayPair, {
         SyntaxKind::ArrayPair,
               SyntaxKind::ListRecursivePairItem
      }
   }
};
#endif

void ArrayPairListItemSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ArrayPairListItemSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, CommaToken, std::set{TokenKindType::T_COMMA});
   syntax_assert_child_kind(raw, ArrayPair, CHILD_NODE_CHOICES.at(Cursor::ArrayPair));
#endif
}

std::optional<TokenSyntax> ArrayPairListItemSyntax::getComma()
{
   RefCountPtr<SyntaxData> commaData = m_data->getChild(Cursor::CommaToken);
   if (!commaData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, commaData.get()};
}

std::optional<Syntax> ArrayPairListItemSyntax::getArrayPair()
{
   RefCountPtr<SyntaxData> arrayPairData = m_data->getChild(Cursor::ArrayPair);
   if (!arrayPairData) {
      return std::nullopt;
   }
   return Syntax {m_root, arrayPairData.get()};
}

ArrayPairListItemSyntax
ArrayPairListItemSyntax::withComma(std::optional<TokenSyntax> comma)
{
   RefCountPtr<RawSyntax> commaRaw;
   if (comma.has_value()) {
      commaRaw = comma->getRaw();
   } else {
      commaRaw = nullptr;
   }
   return m_data->replaceChild<ArrayPairListItemSyntax>(commaRaw, Cursor::ArrayPair);
}

ArrayPairListItemSyntax
ArrayPairListItemSyntax::withArrayPair(std::optional<Syntax> arrayPair)
{
   RefCountPtr<RawSyntax> arrayPairRaw;
   if (arrayPair.has_value()) {
      arrayPairRaw = arrayPair->getRaw();
   } else {
      arrayPairRaw = nullptr;
   }
   return m_data->replaceChild<ArrayPairListItemSyntax>(arrayPairRaw, Cursor::ArrayPair);
}

///
/// ArrayKeyValuePairItemSyntax
///
void ListRecursivePairItemSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ListRecursivePairItemSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, KeyExpr, std::set{SyntaxKind::Expr});
   syntax_assert_child_kind(raw, ArrayPairList, std::set{SyntaxKind::ArrayPairList});
   syntax_assert_child_token(raw, DoubleArrowToken, std::set{TokenKindType::T_DOUBLE_ARROW});
   syntax_assert_child_token(raw, ListToken, std::set{TokenKindType::T_LIST});
   syntax_assert_child_token(raw, LeftParen, std::set{TokenKindType::T_LEFT_PAREN});
   syntax_assert_child_token(raw, RightParen, std::set{TokenKindType::T_RIGHT_PAREN});
#endif
}

std::optional<ExprSyntax> ListRecursivePairItemSyntax::getKeyExpr()
{
   RefCountPtr<SyntaxData> keyExprData = m_data->getChild(Cursor::KeyExpr);
   if (!keyExprData) {
      return std::nullopt;
   }
   return ExprSyntax {m_root, keyExprData.get()};
}

std::optional<TokenSyntax> ListRecursivePairItemSyntax::getDoubleArrowToken()
{
   RefCountPtr<SyntaxData> arrowData = m_data->getChild(Cursor::DoubleArrowToken);
   if (!arrowData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, arrowData.get()};
}

TokenSyntax ListRecursivePairItemSyntax::getListToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::ListToken).get()};
}

TokenSyntax ListRecursivePairItemSyntax::getLeftParen()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftParen).get()};
}

ArrayPairListSyntax ListRecursivePairItemSyntax::getArrayPairList()
{
   return ArrayPairListSyntax {m_root, m_data->getChild(Cursor::ArrayPairList).get()};
}

TokenSyntax ListRecursivePairItemSyntax::getRightParen()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightParen).get()};
}

ListRecursivePairItemSyntax
ListRecursivePairItemSyntax::withKeyExpr(std::optional<ExprSyntax> keyExpr)
{
   RefCountPtr<RawSyntax> keyExprRaw;
   if (keyExpr.has_value()) {
      keyExprRaw = keyExpr->getRaw();
   } else {
      keyExprRaw = nullptr;
   }
   return m_data->replaceChild<ListRecursivePairItemSyntax>(keyExprRaw, Cursor::KeyExpr);
}

ListRecursivePairItemSyntax
ListRecursivePairItemSyntax::withDoubleArrowToken(std::optional<TokenSyntax> doubleArrowToken)
{
   RefCountPtr<RawSyntax> doubleArrowTokenRaw;
   if (doubleArrowToken.has_value()) {
      doubleArrowTokenRaw = doubleArrowToken->getRaw();
   } else {
      doubleArrowTokenRaw = nullptr;
   }
   return m_data->replaceChild<ListRecursivePairItemSyntax>(doubleArrowTokenRaw, Cursor::DoubleArrowToken);
}

ListRecursivePairItemSyntax
ListRecursivePairItemSyntax::withListToken(std::optional<TokenSyntax> listToken)
{
   RefCountPtr<RawSyntax> listTokenRaw;
   if (listToken.has_value()) {
      listTokenRaw = listToken->getRaw();
   } else {
      listTokenRaw = make_missing_token(T_LIST);
   }
   return m_data->replaceChild<ListRecursivePairItemSyntax>(listTokenRaw, Cursor::ArrayPairList);
}

ListRecursivePairItemSyntax
ListRecursivePairItemSyntax::withLeftParen(std::optional<TokenSyntax> leftParen)
{
   RefCountPtr<RawSyntax> leftParenRaw;
   if (leftParen.has_value()) {
      leftParenRaw = leftParen->getRaw();
   } else {
      leftParenRaw = make_missing_token(T_LEFT_PAREN);
   }
   return m_data->replaceChild<ListRecursivePairItemSyntax>(leftParenRaw, Cursor::LeftParen);
}

ListRecursivePairItemSyntax
ListRecursivePairItemSyntax::withArrayPairList(std::optional<ArrayPairListSyntax> pairItemList)
{
   RefCountPtr<RawSyntax> pairItemListRaw;
   if (pairItemList.has_value()) {
      pairItemListRaw = pairItemList->getRaw();
   } else {
      pairItemListRaw = RawSyntax::missing(SyntaxKind::ArrayPairList);
   }
   return m_data->replaceChild<ListRecursivePairItemSyntax>(pairItemListRaw, Cursor::ArrayPairList);
}

ListRecursivePairItemSyntax ListRecursivePairItemSyntax::withRightParen(std::optional<TokenSyntax> rightParen)
{
   RefCountPtr<RawSyntax> rightParenRaw;
   if (rightParen.has_value()) {
      rightParenRaw = rightParen->getRaw();
   } else {
      rightParenRaw = make_missing_token(T_RIGHT_PAREN);
   }
   return m_data->replaceChild<ListRecursivePairItemSyntax>(rightParenRaw, Cursor::RightParen);
}

///
/// SimpleVariableExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType SimpleVariableExprSyntax::CHILD_NODE_CHOICES
{
   {
      SimpleVariableExprSyntax::Variable, {
         SyntaxKind::BraceDecoratedVariableExpr,
               SyntaxKind::SimpleVariableExpr
      }
   }
};
#endif

void SimpleVariableExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == SimpleVariableExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, DollarSign, std::set{TokenKindType::T_DOLLAR_SIGN});
   if (const RefCountPtr<RawSyntax> &variableChild = raw->getChild(Cursor::Variable)) {
      if (variableChild->isToken()) {
         syntax_assert_child_token(raw, Variable, std::set{TokenKindType::T_VARIABLE});
      } else {
         syntax_assert_child_kind(raw, Variable, CHILD_NODE_CHOICES.at(Cursor::Variable));
      }
      if (variableChild->kindOf(SyntaxKind::SimpleVariableExpr)) {
         assert(raw->getChild(Cursor::DollarSign));
      }
   }
#endif
}

std::optional<TokenSyntax> SimpleVariableExprSyntax::getDollarSign()
{
   RefCountPtr<SyntaxData> dollarSignData = m_data->getChild(Cursor::DollarSign);
   if (!dollarSignData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, dollarSignData.get()};
}

Syntax SimpleVariableExprSyntax::getVariable()
{
   return Syntax {m_root, m_data->getChild(Cursor::Variable).get()};
}

SimpleVariableExprSyntax SimpleVariableExprSyntax::withDollarSign(std::optional<TokenSyntax> dollarSign)
{
   RefCountPtr<RawSyntax> dollarSignRaw;
   if (dollarSign.has_value()) {
      dollarSignRaw = dollarSign->getRaw();
   } else {
      dollarSignRaw = nullptr;
   }
   return m_data->replaceChild<SimpleVariableExprSyntax>(dollarSignRaw, Cursor::DollarSign);
}

SimpleVariableExprSyntax SimpleVariableExprSyntax::withVariable(std::optional<Syntax> variable)
{
   RefCountPtr<RawSyntax> variableRaw;
   if (variable.has_value()) {
      variableRaw = variable->getRaw();
   } else {
      variableRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<SimpleVariableExprSyntax>(variableRaw, Cursor::Variable);
}

///
/// ArrayCreateExprSyntax
///
void ArrayCreateExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ArrayCreateExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, ArrayToken, std::set{TokenKindType::T_ARRAY});
   syntax_assert_child_token(raw, LeftParen, std::set{TokenKindType::T_LEFT_PAREN});
   syntax_assert_child_token(raw, RightParen, std::set{TokenKindType::T_RIGHT_PAREN});
   syntax_assert_child_kind(raw, PairItemList, std::set{SyntaxKind::ArrayPairList});
#endif
}

TokenSyntax ArrayCreateExprSyntax::getArrayToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::ArrayToken).get()};
}

TokenSyntax ArrayCreateExprSyntax::getLeftParen()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftParen).get()};
}

ArrayPairListSyntax ArrayCreateExprSyntax::getPairItemList()
{
   return ArrayPairListSyntax {m_root, m_data->getChild(Cursor::PairItemList).get()};
}

TokenSyntax ArrayCreateExprSyntax::getRightParen()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightParen).get()};
}

ArrayCreateExprSyntax ArrayCreateExprSyntax::withArrayToken(std::optional<TokenSyntax> arrayToken)
{
   RefCountPtr<RawSyntax> arrayTokenRaw;
   if (arrayToken.has_value()) {
      arrayTokenRaw = arrayToken->getRaw();
   } else {
      arrayTokenRaw = RawSyntax::missing(TokenKindType::T_ARRAY,
                                         OwnedString::makeUnowned(get_token_text(TokenKindType::T_ARRAY)));
   }
   return m_data->replaceChild<ArrayCreateExprSyntax>(arrayTokenRaw, Cursor::ArrayToken);
}

ArrayCreateExprSyntax ArrayCreateExprSyntax::withLeftParen(std::optional<TokenSyntax> leftParen)
{
   RefCountPtr<RawSyntax> leftParanRaw;
   if (leftParen.has_value()) {
      leftParanRaw = leftParen->getRaw();
   } else {
      leftParanRaw = RawSyntax::missing(TokenKindType::T_LEFT_PAREN,
                                        OwnedString::makeUnowned(get_token_text(TokenKindType::T_LEFT_PAREN)));
   }
   return m_data->replaceChild<ArrayCreateExprSyntax>(leftParanRaw, Cursor::LeftParen);
}

ArrayCreateExprSyntax ArrayCreateExprSyntax::withPairItemList(std::optional<ArrayPairListSyntax> pairItemList)
{
   RefCountPtr<RawSyntax> pairItemListRaw;
   if (pairItemList.has_value()) {
      pairItemListRaw = pairItemList->getRaw();
   } else {
      pairItemListRaw = RawSyntax::missing(SyntaxKind::ArrayPairList);
   }
   return m_data->replaceChild<ArrayCreateExprSyntax>(pairItemListRaw, Cursor::PairItemList);
}

ArrayCreateExprSyntax ArrayCreateExprSyntax::withRightParen(std::optional<TokenSyntax> rightParen)
{
   RefCountPtr<RawSyntax> rightParenRaw;
   if (rightParen.has_value()) {
      rightParenRaw = rightParen->getRaw();
   } else {
      rightParenRaw = RawSyntax::missing(TokenKindType::T_RIGHT_PAREN,
                                         OwnedString::makeUnowned(get_token_text(TokenKindType::T_RIGHT_PAREN)));
   }
   return m_data->replaceChild<ArrayCreateExprSyntax>(rightParenRaw, Cursor::RightParen);
}

///
/// SimplifiedArrayCreateExprSyntax
///
void SimplifiedArrayCreateExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == SimplifiedArrayCreateExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, LeftSquareBracket, std::set{TokenKindType::T_LEFT_SQUARE_BRACKET});
   syntax_assert_child_token(raw, RightSquareBracket, std::set{TokenKindType::T_RIGHT_SQUARE_BRACKET});
   syntax_assert_child_kind(raw, PairItemList, std::set{SyntaxKind::ArrayPairList});
#endif
}

TokenSyntax SimplifiedArrayCreateExprSyntax::getLeftSquareBracket()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftSquareBracket).get()};
}

ArrayPairListSyntax SimplifiedArrayCreateExprSyntax::getPairItemList()
{
   return ArrayPairListSyntax {m_root, m_data->getChild(Cursor::PairItemList).get()};
}

TokenSyntax SimplifiedArrayCreateExprSyntax::getRightSquareBracket()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightSquareBracket).get()};
}

SimplifiedArrayCreateExprSyntax
SimplifiedArrayCreateExprSyntax::withLeftSquareBracket(std::optional<TokenSyntax> leftSquareBracket)
{
   RefCountPtr<RawSyntax> leftSquareBracketRaw;
   if (leftSquareBracket.has_value()) {
      leftSquareBracketRaw = leftSquareBracket->getRaw();
   } else {
      leftSquareBracketRaw = RawSyntax::missing(TokenKindType::T_LEFT_SQUARE_BRACKET,
                                                OwnedString::makeUnowned(get_token_text(TokenKindType::T_LEFT_SQUARE_BRACKET)));
   }
   return m_data->replaceChild<SimplifiedArrayCreateExprSyntax>(leftSquareBracketRaw, Cursor::LeftSquareBracket);
}

SimplifiedArrayCreateExprSyntax
SimplifiedArrayCreateExprSyntax::withPairItemList(std::optional<ArrayPairListSyntax> pairItemList)
{
   RefCountPtr<RawSyntax> pairItemListRaw;
   if (pairItemList.has_value()) {
      pairItemListRaw = pairItemList->getRaw();
   } else {
      pairItemListRaw = RawSyntax::missing(SyntaxKind::ArrayPairList);
   }
   return m_data->replaceChild<SimplifiedArrayCreateExprSyntax>(pairItemListRaw, Cursor::PairItemList);
}

SimplifiedArrayCreateExprSyntax
SimplifiedArrayCreateExprSyntax::withRightSquareBracket(std::optional<TokenSyntax> rightSquareBracket)
{
   RefCountPtr<RawSyntax> rightSquareBracketRaw;
   if (rightSquareBracket.has_value()) {
      rightSquareBracketRaw = rightSquareBracket->getRaw();
   } else {
      rightSquareBracketRaw = RawSyntax::missing(TokenKindType::T_RIGHT_SQUARE_BRACKET,
                                                 OwnedString::makeUnowned(get_token_text(TokenKindType::T_RIGHT_SQUARE_BRACKET)));
   }
   return m_data->replaceChild<SimplifiedArrayCreateExprSyntax>(rightSquareBracketRaw, Cursor::RightSquareBracket);
}

///
/// ArrayAccessExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType ArrayAccessExprSyntax::CHILD_NODE_CHOICES
{
   {
      ArrayAccessExprSyntax::ArrayRef, {
         SyntaxKind::NewVariableClause, SyntaxKind::DereferencableClause,
               SyntaxKind::ConstExpr
      }
   },
   {
      ArrayAccessExprSyntax::Offset, {
         SyntaxKind::EncapsVariableOffset, SyntaxKind::OptionalExpr,
      }
   }
};
#endif

void ArrayAccessExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ArrayAccessExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, LeftSquareBracket, std::set{TokenKindType::T_LEFT_SQUARE_BRACKET});
   syntax_assert_child_token(raw, RightSquareBracket, std::set{TokenKindType::T_RIGHT_SQUARE_BRACKET});
   syntax_assert_child_kind(raw, Offset, CHILD_NODE_CHOICES.at(Cursor::Offset));
   if (const RefCountPtr<RawSyntax> &arrayRefChild = raw->getChild(Cursor::ArrayRef)) {
      if (arrayRefChild->isToken()) {
         syntax_assert_child_token(raw, ArrayRef, std::set{TokenKindType::T_VARIABLE});
      } else {
         syntax_assert_child_kind(raw, ArrayRef, CHILD_NODE_CHOICES.at(Cursor::ArrayRef));
      }
   }
#endif
}

Syntax ArrayAccessExprSyntax::getArrayRef()
{
   return Syntax {m_root, m_data->getChild(Cursor::ArrayRef).get()};
}

TokenSyntax ArrayAccessExprSyntax::getLeftSquareBracket()
{
   return TokenSyntax {m_root, m_data->getChild(LeftSquareBracket).get()};
}

Syntax ArrayAccessExprSyntax::getOffset()
{
   return Syntax {m_root, m_data->getChild(Cursor::Offset).get()};
}

TokenSyntax ArrayAccessExprSyntax::getRightSquareBracket()
{
   return TokenSyntax {m_root, m_data->getChild(RightSquareBracket).get()};
}

ArrayAccessExprSyntax
ArrayAccessExprSyntax::withArrayRef(std::optional<Syntax> arrayRef)
{
   RefCountPtr<RawSyntax> arrayRefRaw;
   if (arrayRef.has_value()) {
      arrayRefRaw = arrayRef->getRaw();
   } else {
      arrayRefRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<ArrayAccessExprSyntax>(arrayRefRaw, Cursor::ArrayRef);
}

ArrayAccessExprSyntax
ArrayAccessExprSyntax::withLeftSquareBracket(std::optional<TokenSyntax> leftSquareBracket)
{
   RefCountPtr<RawSyntax> leftSquareBracketRaw;
   if (leftSquareBracket.has_value()) {
      leftSquareBracketRaw = leftSquareBracket->getRaw();
   } else {
      leftSquareBracketRaw = make_missing_token(T_LEFT_SQUARE_BRACKET);
   }
   return m_data->replaceChild<ArrayAccessExprSyntax>(leftSquareBracketRaw, Cursor::LeftSquareBracket);
}

ArrayAccessExprSyntax ArrayAccessExprSyntax::withOffset(std::optional<Syntax> offset)
{
   RefCountPtr<RawSyntax> offsetRaw;
   if (offset.has_value()) {
      offsetRaw = offset->getRaw();
   } else {
      offsetRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<ArrayAccessExprSyntax>(offsetRaw, Cursor::Offset);
}

ArrayAccessExprSyntax
ArrayAccessExprSyntax::withRightSquareBracket(std::optional<TokenSyntax> rightSquareBracket)
{
   RefCountPtr<RawSyntax> rightSquareBracketRaw;
   if (rightSquareBracket.has_value()) {
      rightSquareBracketRaw = rightSquareBracket->getRaw();
   } else {
      rightSquareBracketRaw = make_missing_token(T_RIGHT_SQUARE_BRACKET);
   }
   return m_data->replaceChild<ArrayAccessExprSyntax>(rightSquareBracketRaw, Cursor::RightSquareBracket);
}

///
/// BraceDecoratedArrayAccessExprSyntax
///

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType BraceDecoratedArrayAccessExprSyntax::CHILD_NODE_CHOICES
{
   {
      BraceDecoratedArrayAccessExprSyntax::ArrayRef, {
         SyntaxKind::NewVariableClause, SyntaxKind::DereferencableClause
      }
   }
};
#endif

void BraceDecoratedArrayAccessExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == BraceDecoratedArrayAccessExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, ArrayRef, CHILD_NODE_CHOICES.at(Cursor::ArrayRef));
   syntax_assert_child_kind(raw, OffsetExpr, std::set{SyntaxKind::BraceDecoratedExprClause});
#endif
}

Syntax BraceDecoratedArrayAccessExprSyntax::getArrayRef()
{
   return Syntax {m_root, m_data->getChild(Cursor::ArrayRef).get()};
}

BraceDecoratedExprClauseSyntax BraceDecoratedArrayAccessExprSyntax::getOffsetExpr()
{
   return BraceDecoratedExprClauseSyntax {m_root, m_data->getChild(Cursor::OffsetExpr).get()};
}

BraceDecoratedArrayAccessExprSyntax
BraceDecoratedArrayAccessExprSyntax::withArrayRef(std::optional<Syntax> arrayRef)
{
   RefCountPtr<RawSyntax> arrayRefRaw;
   if (arrayRef.has_value()) {
      arrayRefRaw = arrayRef->getRaw();
   } else {
      arrayRefRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<BraceDecoratedArrayAccessExprSyntax>(arrayRefRaw, Cursor::ArrayRef);
}

BraceDecoratedArrayAccessExprSyntax
BraceDecoratedArrayAccessExprSyntax::withOffsetExpr(std::optional<BraceDecoratedExprClauseSyntax> offsetExpr)
{
   RefCountPtr<RawSyntax> offsetExprRaw;
   if (offsetExpr.has_value()) {
      offsetExprRaw = offsetExpr->getRaw();
   } else {
      offsetExprRaw = RawSyntax::missing(SyntaxKind::BraceDecoratedExprClause);
   }
   return m_data->replaceChild<BraceDecoratedArrayAccessExprSyntax>(offsetExprRaw, Cursor::OffsetExpr);
}

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType SimpleFunctionCallExprSyntax::CHILD_NODE_CHOICES
{
   {
      SimpleFunctionCallExprSyntax::FuncName, {
         SyntaxKind::Name, SyntaxKind::CallableFuncNameClause
      }
   }
};
#endif

void SimpleFunctionCallExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == SimpleFunctionCallExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, FuncName, CHILD_NODE_CHOICES.at(Cursor::FuncName));
   syntax_assert_child_kind(raw, ArgumentsClause, std::set{SyntaxKind::ArgumentListClause});
#endif
}

Syntax SimpleFunctionCallExprSyntax::getFuncName()
{
   return Syntax {m_root, m_data->getChild(Cursor::FuncName).get()};
}

ArgumentListClauseSyntax SimpleFunctionCallExprSyntax::getArgumentsClause()
{
   return ArgumentListClauseSyntax {m_root, m_data->getChild(Cursor::ArgumentsClause).get()};
}

SimpleFunctionCallExprSyntax
SimpleFunctionCallExprSyntax::withFuncName(std::optional<Syntax> funcName)
{
   RefCountPtr<RawSyntax> funcNameRaw;
   if (funcName.has_value()) {
      funcNameRaw = funcName->getRaw();
   } else {
      funcNameRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<SimpleFunctionCallExprSyntax>(funcNameRaw, Cursor::FuncName);
}

SimpleFunctionCallExprSyntax
SimpleFunctionCallExprSyntax::withArgumentsClause(std::optional<ArgumentListClauseSyntax> argumentsClause)
{
   RefCountPtr<RawSyntax> argumentsClauseRaw;
   if (argumentsClause.has_value()) {
      argumentsClauseRaw = argumentsClause->getRaw();
   } else {
      argumentsClauseRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<SimpleFunctionCallExprSyntax>(argumentsClauseRaw, Cursor::ArgumentsClause);
}

///
/// FunctionCallExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType FunctionCallExprSyntax::CHILD_NODE_CHOICES
{
   {
      FunctionCallExprSyntax::Callable, {
         SyntaxKind::SimpleFunctionCallExpr, SyntaxKind::StaticMethodCallExpr
      }
   }
};
#endif

void FunctionCallExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == FunctionCallExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Callable, CHILD_NODE_CHOICES.at(Cursor::Callable));
#endif
}

ExprSyntax FunctionCallExprSyntax::getCallable()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Callable).get()};
}

FunctionCallExprSyntax FunctionCallExprSyntax::withCallable(std::optional<ExprSyntax> callable)
{
   RefCountPtr<RawSyntax> callableRaw;
   if (callable.has_value()) {
      callableRaw = callable->getRaw();
   } else {
      callableRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<FunctionCallExprSyntax>(callableRaw, Cursor::Callable);
}

///
/// InstanceMethodCallExprSyntax
///
void InstanceMethodCallExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == InstanceMethodCallExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, QualifiedMethodName, std::set{SyntaxKind::InstancePropertyExpr});
   syntax_assert_child_kind(raw, ArgumentListClause, std::set{SyntaxKind::ArgumentListClause});
#endif
}

InstancePropertyExprSyntax InstanceMethodCallExprSyntax::getQualifiedMethodName()
{
   return InstancePropertyExprSyntax {m_root, m_data->getChild(Cursor::QualifiedMethodName).get()};
}

ArgumentListClauseSyntax InstanceMethodCallExprSyntax::getArgumentListClause()
{
   return ArgumentListClauseSyntax {m_root, m_data->getChild(Cursor::ArgumentListClause).get()};
}

InstanceMethodCallExprSyntax
InstanceMethodCallExprSyntax::withQualifiedMethodName(std::optional<InstancePropertyExprSyntax> methodName)
{
   RefCountPtr<RawSyntax> methodNameRaw;
   if (methodName.has_value()) {
      methodNameRaw = methodName->getRaw();
   } else {
      methodNameRaw = RawSyntax::missing(SyntaxKind::InstancePropertyExpr);
   }
   return m_data->replaceChild<InstanceMethodCallExprSyntax>(methodNameRaw, Cursor::QualifiedMethodName);
}

InstanceMethodCallExprSyntax
InstanceMethodCallExprSyntax::withArgumentListClause(std::optional<ArgumentListClauseSyntax> arguments)
{
   RefCountPtr<RawSyntax> argumentsRaw;
   if (arguments.has_value()) {
      argumentsRaw = arguments->getRaw();
   } else {
      argumentsRaw = RawSyntax::missing(SyntaxKind::ArgumentListClause);
   }
   return m_data->replaceChild<InstanceMethodCallExprSyntax>(argumentsRaw, Cursor::ArgumentListClause);
}

///
/// StaticMethodCallExprSyntax
///

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType StaticMethodCallExprSyntax::CHILD_NODE_CHOICES
{
   {
      StaticMethodCallExprSyntax::ClassName, {
         SyntaxKind::ClassNameClause, SyntaxKind::VariableClassNameClause,
      }
   }
};
#endif

void StaticMethodCallExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == StaticMethodCallExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, ClassName, CHILD_NODE_CHOICES.at(Cursor::ClassName));
   syntax_assert_child_token(raw, Separator, std::set{TokenKindType::T_PAAMAYIM_NEKUDOTAYIM});
   syntax_assert_child_kind(raw, MethodName, std::set{SyntaxKind::MemberNameClause});
   syntax_assert_child_kind(raw, Arguments, std::set{SyntaxKind::ArgumentListClause});
#endif
}

Syntax StaticMethodCallExprSyntax::getClassName()
{
   return Syntax {m_root, m_data->getChild(Cursor::ClassName).get()};
}

TokenSyntax StaticMethodCallExprSyntax::getSeparator()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Separator).get()};
}

MemberNameClauseSyntax StaticMethodCallExprSyntax::getMethodName()
{
   return MemberNameClauseSyntax {m_root, m_data->getChild(Cursor::MethodName).get()};
}

ArgumentListClauseSyntax StaticMethodCallExprSyntax::getArguments()
{
   return ArgumentListClauseSyntax {m_root, m_data->getChild(Cursor::Arguments).get()};
}

StaticMethodCallExprSyntax
StaticMethodCallExprSyntax::withClassName(std::optional<Syntax> className)
{
   RefCountPtr<RawSyntax> classNameRaw;
   if (className.has_value()) {
      classNameRaw = className->getRaw();
   } else {
      classNameRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<StaticMethodCallExprSyntax>(classNameRaw, Cursor::ClassName);
}

StaticMethodCallExprSyntax
StaticMethodCallExprSyntax::withSeparator(std::optional<TokenSyntax> separator)
{
   RefCountPtr<RawSyntax> separatorRaw;
   if (separator.has_value()) {
      separatorRaw = separator->getRaw();
   } else {
      separatorRaw = make_missing_token(T_PAAMAYIM_NEKUDOTAYIM);
   }
   return m_data->replaceChild<StaticMethodCallExprSyntax>(separatorRaw, Cursor::Separator);
}

StaticMethodCallExprSyntax
StaticMethodCallExprSyntax::withMethodName(std::optional<MemberNameClauseSyntax> methodName)
{
   RefCountPtr<RawSyntax> methodNameRaw;
   if (methodName.has_value()) {
      methodNameRaw = methodName->getRaw();
   } else {
      methodNameRaw = RawSyntax::missing(SyntaxKind::MemberNameClause);
   }
   return m_data->replaceChild<StaticMethodCallExprSyntax>(methodNameRaw, Cursor::MethodName);
}

StaticMethodCallExprSyntax
StaticMethodCallExprSyntax::withArguments(std::optional<ArgumentListClauseSyntax> arguments)
{
   RefCountPtr<RawSyntax> argumentsRaw;
   if (arguments.has_value()) {
      argumentsRaw = arguments->getRaw();
   } else {
      argumentsRaw = RawSyntax::missing(SyntaxKind::ArgumentListClause);
   }
   return m_data->replaceChild<StaticMethodCallExprSyntax>(argumentsRaw, Cursor::Arguments);
}

///
/// DereferencableScalarExprSyntax
///

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType DereferencableScalarExprSyntax::CHILD_NODE_CHOICES
{
   {
      DereferencableScalarExprSyntax::ScalarValue, {
         SyntaxKind::ArrayCreateExpr, SyntaxKind::SimplifiedArrayCreateExpr,
      }
   }
};
#endif

void DereferencableScalarExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == DereferencableScalarExprSyntax::CHILDREN_COUNT);
   if (const RefCountPtr<RawSyntax> &valueChild = raw->getChild(Cursor::ScalarValue)) {
      if (valueChild->isToken()) {
         syntax_assert_child_token(raw, ScalarValue, std::set{TokenKindType::T_CONSTANT_ENCAPSED_STRING});
      } else {
         syntax_assert_child_kind(raw, ScalarValue, CHILD_NODE_CHOICES.at(Cursor::ScalarValue));
      }
   }
#endif
}

Syntax DereferencableScalarExprSyntax::getScalarValue()
{
   return Syntax {m_root, m_data->getChild(Cursor::ScalarValue).get()};
}

DereferencableScalarExprSyntax
DereferencableScalarExprSyntax::withScalarValue(std::optional<Syntax> scalarValue)
{
   RefCountPtr<RawSyntax> scalarValueRaw;
   if (scalarValue.has_value()) {
      scalarValueRaw = scalarValue->getRaw();
   } else {
      scalarValueRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<DereferencableScalarExprSyntax>(scalarValueRaw, Cursor::ScalarValue);
}

///
/// AnonymousClassDefinitionClauseSyntax
///
void AnonymousClassDefinitionClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == AnonymousClassDefinitionClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, ClassToken, std::set{TokenKindType::T_CLASS});
   syntax_assert_child_kind(raw, CtorArguments, std::set{SyntaxKind::ArgumentListClause});
   syntax_assert_child_kind(raw, ExtendsFrom, std::set{SyntaxKind::ExtendsFromClause});
   syntax_assert_child_kind(raw, ImplementsList, std::set{SyntaxKind::ImplementsClause});
   syntax_assert_child_kind(raw, Members, std::set{SyntaxKind::MemberDeclBlock});
#endif
}

TokenSyntax AnonymousClassDefinitionClauseSyntax::getClassToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::ClassToken).get()};
}

std::optional<ArgumentListClauseSyntax> AnonymousClassDefinitionClauseSyntax::getCtorArguments()
{
   RefCountPtr<SyntaxData> ctorArgsData = m_data->getChild(Cursor::CtorArguments);
   if (!ctorArgsData) {
      return std::nullopt;
   }
   return ArgumentListClauseSyntax {m_root, ctorArgsData.get()};
}

std::optional<ExtendsFromClauseSyntax> AnonymousClassDefinitionClauseSyntax::getExtendsFrom()
{
   RefCountPtr<SyntaxData> extendsFromData = m_data->getChild(Cursor::ExtendsFrom);
   if (!extendsFromData) {
      return std::nullopt;
   }
   return ExtendsFromClauseSyntax {m_root, extendsFromData.get()};
}

std::optional<ImplementsClauseSyntax> AnonymousClassDefinitionClauseSyntax::getImplementsList()
{
   RefCountPtr<SyntaxData> implementsListData = m_data->getChild(Cursor::ImplementsList);
   if (!implementsListData) {
      return std::nullopt;
   }
   return ImplementsClauseSyntax {m_root, implementsListData.get()};
}

MemberDeclBlockSyntax AnonymousClassDefinitionClauseSyntax::getMembers()
{
   return MemberDeclBlockSyntax {m_root, m_data->getChild(Cursor::Members).get()};
}

AnonymousClassDefinitionClauseSyntax
AnonymousClassDefinitionClauseSyntax::withClassToken(std::optional<TokenSyntax> classToken)
{
   RefCountPtr<RawSyntax> classTokenRaw;
   if (classToken.has_value()) {
      classTokenRaw = classToken->getRaw();
   } else {
      classTokenRaw = RawSyntax::missing(TokenKindType::T_CLASS,
                                         OwnedString::makeUnowned(get_token_text(TokenKindType::T_CLASS)));
   }
   return m_data->replaceChild<AnonymousClassDefinitionClauseSyntax>(classTokenRaw, Cursor::ClassToken);
}

AnonymousClassDefinitionClauseSyntax
AnonymousClassDefinitionClauseSyntax::withCtorArguments(std::optional<ArgumentListClauseSyntax> ctorArguments)
{
   RefCountPtr<RawSyntax> ctorArgumentsRaw;
   if (ctorArguments.has_value()) {
      ctorArgumentsRaw = ctorArguments->getRaw();
   } else {
      ctorArgumentsRaw = RawSyntax::missing(SyntaxKind::ArgumentListClause);
   }
   return m_data->replaceChild<AnonymousClassDefinitionClauseSyntax>(ctorArgumentsRaw, Cursor::CtorArguments);
}

AnonymousClassDefinitionClauseSyntax
AnonymousClassDefinitionClauseSyntax::withExtendsFrom(std::optional<ExtendsFromClauseSyntax> extends)
{
   RefCountPtr<RawSyntax> extendsRaw;
   if (extends.has_value()) {
      extendsRaw = extends->getRaw();
   } else {
      extendsRaw = RawSyntax::missing(SyntaxKind::ExtendsFromClause);
   }
   return m_data->replaceChild<AnonymousClassDefinitionClauseSyntax>(extendsRaw, Cursor::ExtendsFrom);
}

AnonymousClassDefinitionClauseSyntax
AnonymousClassDefinitionClauseSyntax::withImplementsList(std::optional<ImplementsClauseSyntax> implements)
{
   RefCountPtr<RawSyntax> implementsRaw;
   if (implements.has_value()) {
      implementsRaw = implements->getRaw();
   } else {
      implementsRaw = RawSyntax::missing(SyntaxKind::ImplementsClause);
   }
   return m_data->replaceChild<AnonymousClassDefinitionClauseSyntax>(implementsRaw, Cursor::ImplementsList);
}

AnonymousClassDefinitionClauseSyntax
AnonymousClassDefinitionClauseSyntax::withMembers(std::optional<MemberDeclBlockSyntax> members)
{
   RefCountPtr<RawSyntax> membersRaw;
   if (members.has_value()) {
      membersRaw = members->getRaw();
   } else {
      membersRaw = RawSyntax::missing(SyntaxKind::MemberDeclBlock);
   }
   return m_data->replaceChild<AnonymousClassDefinitionClauseSyntax>(membersRaw, Cursor::Members);
}

///
/// SimpleInstanceCreateExprSyntax
///
void SimpleInstanceCreateExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == SimpleInstanceCreateExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, NewToken, std::set{TokenKindType::T_NEW});
   syntax_assert_child_kind(raw, ClassName, std::set{SyntaxKind::ClassNameRefClause});
   syntax_assert_child_kind(raw, CtorArgsClause, std::set{SyntaxKind::ArgumentListClause});
#endif
}

TokenSyntax SimpleInstanceCreateExprSyntax::getNewToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::NewToken).get()};
}

ClassNameRefClauseSyntax SimpleInstanceCreateExprSyntax::getClassName()
{
   return ClassNameRefClauseSyntax {m_root, m_data->getChild(Cursor::ClassName).get()};
}

std::optional<ArgumentListClauseSyntax> SimpleInstanceCreateExprSyntax::getCtorArgsClause()
{
   RefCountPtr<SyntaxData> argsData = m_data->getChild(Cursor::CtorArgsClause);
   if (!argsData) {
      return std::nullopt;
   }
   return ArgumentListClauseSyntax {m_root, argsData.get()};
}

SimpleInstanceCreateExprSyntax
SimpleInstanceCreateExprSyntax::withNewToken(std::optional<TokenSyntax> newToken)
{
   RefCountPtr<RawSyntax> newTokenRaw;
   if (newToken.has_value()) {
      newTokenRaw = newToken->getRaw();
   } else {
      newTokenRaw = make_missing_token(T_NEW);
   }
   return m_data->replaceChild<SimpleInstanceCreateExprSyntax>(newTokenRaw, Cursor::NewToken);
}

SimpleInstanceCreateExprSyntax
SimpleInstanceCreateExprSyntax::withClassName(std::optional<ClassNameRefClauseSyntax> className)
{
   RefCountPtr<RawSyntax> classNameRaw;
   if (className.has_value()) {
      classNameRaw = className->getRaw();
   } else {
      classNameRaw = RawSyntax::missing(SyntaxKind::ClassNameRefClause);
   }
   return m_data->replaceChild<SimpleInstanceCreateExprSyntax>(classNameRaw, Cursor::ClassName);
}

SimpleInstanceCreateExprSyntax
SimpleInstanceCreateExprSyntax::withCtorArgsClause(std::optional<ArgumentListClauseSyntax> argsClause)
{
   RefCountPtr<RawSyntax> argsClauseRaw;
   if (argsClause.has_value()) {
      argsClauseRaw = argsClause->getRaw();
   } else {
      argsClauseRaw = nullptr;
   }
   return m_data->replaceChild<SimpleInstanceCreateExprSyntax>(argsClauseRaw, Cursor::CtorArgsClause);
}

///
/// AnonymousInstanceCreateExprSyntax
///
void AnonymousInstanceCreateExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == AnonymousInstanceCreateExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, NewToken, std::set{TokenKindType::T_NEW});
   syntax_assert_child_kind(raw, AnonymousClassDef, std::set{SyntaxKind::AnonymousClassDefinitionClause});
#endif
}

TokenSyntax AnonymousInstanceCreateExprSyntax::getNewToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::NewToken).get()};
}

AnonymousClassDefinitionClauseSyntax AnonymousInstanceCreateExprSyntax::getAnonymousClassDef()
{
   return AnonymousClassDefinitionClauseSyntax {m_root, m_data->getChild(Cursor::AnonymousClassDef).get()};
}

AnonymousInstanceCreateExprSyntax
AnonymousInstanceCreateExprSyntax::withNewToken(std::optional<TokenSyntax> newToken)
{
   RefCountPtr<RawSyntax> newTokenRaw;
   if (newToken.has_value()) {
      newTokenRaw = newToken->getRaw();
   } else {
      newTokenRaw = make_missing_token(T_NEW);
   }
   return m_data->replaceChild<AnonymousInstanceCreateExprSyntax>(newTokenRaw, Cursor::NewToken);
}

AnonymousInstanceCreateExprSyntax
AnonymousInstanceCreateExprSyntax::withAnonymousClassDef(std::optional<AnonymousClassDefinitionClauseSyntax> classDef)
{
   RefCountPtr<RawSyntax> classDefRaw;
   if (classDef.has_value()) {
      classDefRaw = classDef->getRaw();
   } else {
      classDefRaw = RawSyntax::missing(SyntaxKind::AnonymousClassDefinitionClause);
   }
   return m_data->replaceChild<AnonymousInstanceCreateExprSyntax>(classDefRaw, Cursor::AnonymousClassDef);
}

///
/// ClassicLambdaExprSyntax
///
void ClassicLambdaExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ClassicLambdaExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, FuncToken, std::set{TokenKindType::T_FUNCTION});
   syntax_assert_child_token(raw, ReturnRefToken, std::set{TokenKindType::T_AMPERSAND});
   syntax_assert_child_kind(raw, ParameterListClause, std::set{SyntaxKind::ParameterListClause});
   syntax_assert_child_kind(raw, LexicalVarsClause, std::set{SyntaxKind::UseLexicalVarClause});
   syntax_assert_child_kind(raw, ReturnType, std::set{SyntaxKind::ReturnTypeClause});
   syntax_assert_child_kind(raw, Body, std::set{SyntaxKind::InnerCodeBlockStmt});
#endif
}

TokenSyntax ClassicLambdaExprSyntax::getFuncToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::FuncToken).get()};
}

std::optional<TokenSyntax> ClassicLambdaExprSyntax::getReturnRefToken()
{
   RefCountPtr<SyntaxData> returnRefFlagData = m_data->getChild(Cursor::ReturnRefToken);
   if (!returnRefFlagData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, returnRefFlagData.get()};
}

ParameterClauseSyntax ClassicLambdaExprSyntax::getParameterListClause()
{
   return ParameterClauseSyntax {m_root, m_data->getChild(Cursor::ParameterListClause).get()};
}

std::optional<UseLexicalVariableClauseSyntax> ClassicLambdaExprSyntax::getLexicalVarsClause()
{
   RefCountPtr<SyntaxData> lexicalVarsData = m_data->getChild(Cursor::LexicalVarsClause);
   if (!lexicalVarsData) {
      return std::nullopt;
   }
   return UseLexicalVariableClauseSyntax {m_root, lexicalVarsData.get()};
}

std::optional<ReturnTypeClauseSyntax> ClassicLambdaExprSyntax::getReturnType()
{
   RefCountPtr<SyntaxData> returnTypeData = m_data->getChild(Cursor::ReturnType);
   if (!returnTypeData) {
      return std::nullopt;
   }
   return ReturnTypeClauseSyntax {m_root, returnTypeData.get()};
}

InnerCodeBlockStmtSyntax ClassicLambdaExprSyntax::getBody()
{
   return InnerCodeBlockStmtSyntax {m_root, m_data->getChild(Cursor::Body).get()};
}

ClassicLambdaExprSyntax
ClassicLambdaExprSyntax::withFuncToken(std::optional<TokenSyntax> funcToken)
{
   RefCountPtr<RawSyntax> funcTokenRaw;
   if (funcToken.has_value()) {
      funcTokenRaw = funcToken->getRaw();
   } else {
      funcTokenRaw = make_missing_token(T_FUNCTION);
   }
   return m_data->replaceChild<ClassicLambdaExprSyntax>(funcTokenRaw, Cursor::FuncToken);
}

ClassicLambdaExprSyntax
ClassicLambdaExprSyntax::withReturnRefToken(std::optional<TokenSyntax> returnRefToken)
{
   RefCountPtr<RawSyntax> returnRefTokenRaw;
   if (returnRefToken.has_value()) {
      returnRefTokenRaw = returnRefToken->getRaw();
   } else {
      returnRefTokenRaw = make_missing_token(T_AMPERSAND);
   }
   return m_data->replaceChild<ClassicLambdaExprSyntax>(returnRefTokenRaw, Cursor::ReturnRefToken);
}

ClassicLambdaExprSyntax
ClassicLambdaExprSyntax::withParameterListClause(std::optional<ParameterClauseSyntax> parameterListClause)
{
   RefCountPtr<RawSyntax> parameterListClauseRaw;
   if (parameterListClause.has_value()) {
      parameterListClauseRaw = parameterListClause->getRaw();
   } else {
      parameterListClauseRaw = RawSyntax::missing(SyntaxKind::ParameterListClause);
   }
   return m_data->replaceChild<ClassicLambdaExprSyntax>(parameterListClauseRaw, Cursor::ParameterListClause);
}

ClassicLambdaExprSyntax
ClassicLambdaExprSyntax::withLexicalVarsClause(std::optional<UseLexicalVariableClauseSyntax> lexicalVars)
{
   RefCountPtr<RawSyntax> lexicalVarsRaw;
   if (lexicalVars.has_value()) {
      lexicalVarsRaw = lexicalVars->getRaw();
   } else {
      lexicalVarsRaw = RawSyntax::missing(SyntaxKind::UseLexicalVarClause);
   }
   return m_data->replaceChild<ClassicLambdaExprSyntax>(lexicalVarsRaw, Cursor::LexicalVarsClause);
}

ClassicLambdaExprSyntax
ClassicLambdaExprSyntax::withReturnType(std::optional<ReturnTypeClauseSyntax> returnType)
{
   RefCountPtr<RawSyntax> returnTypeRaw;
   if (returnType.has_value()) {
      returnTypeRaw = returnType->getRaw();
   } else {
      returnTypeRaw = RawSyntax::missing(SyntaxKind::ReturnTypeClause);
   }
   return m_data->replaceChild<ClassicLambdaExprSyntax>(returnTypeRaw, Cursor::ReturnType);
}

ClassicLambdaExprSyntax
ClassicLambdaExprSyntax::withBody(std::optional<InnerCodeBlockStmtSyntax> body)
{
   RefCountPtr<RawSyntax> bodyRaw;
   if (body.has_value()) {
      bodyRaw = body->getRaw();
   } else {
      bodyRaw = RawSyntax::missing(SyntaxKind::InnerCodeBlockStmt);
   }
   return m_data->replaceChild<ClassicLambdaExprSyntax>(bodyRaw, Cursor::Body);
}

///
/// SimplifiedLambdaExprSyntax
///
void SimplifiedLambdaExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == SimplifiedLambdaExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, FnToken, std::set{TokenKindType::T_FUNCTION});
   syntax_assert_child_token(raw, ReturnRefToken, std::set{TokenKindType::T_AMPERSAND});
   syntax_assert_child_token(raw, DoubleArrowToken, std::set{TokenKindType::T_DOUBLE_ARROW});
   syntax_assert_child_kind(raw, ParameterListClause, std::set{SyntaxKind::ParameterListClause});
   syntax_assert_child_kind(raw, ReturnType, std::set{SyntaxKind::ReturnTypeClause});
   syntax_assert_child_kind(raw, Body, std::set{SyntaxKind::Expr});
#endif
}

TokenSyntax SimplifiedLambdaExprSyntax::getFnToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::FnToken).get()};
}

std::optional<TokenSyntax> SimplifiedLambdaExprSyntax::getReturnRefToken()
{
   RefCountPtr<SyntaxData> returnRefData = m_data->getChild(Cursor::ReturnRefToken);
   if (!returnRefData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, returnRefData.get()};
}

ParameterClauseSyntax SimplifiedLambdaExprSyntax::getParameterListClause()
{
   return ParameterClauseSyntax {m_root, m_data->getChild(Cursor::ParameterListClause).get()};
}

std::optional<ReturnTypeClauseSyntax> SimplifiedLambdaExprSyntax::getReturnType()
{
   RefCountPtr<SyntaxData> returnTypeData = m_data->getChild(Cursor::ReturnType);
   if (!returnTypeData) {
      return std::nullopt;
   }
   return ReturnTypeClauseSyntax {m_root, returnTypeData.get()};
}

TokenSyntax SimplifiedLambdaExprSyntax::getDoubleArrowToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::DoubleArrowToken).get()};
}

ExprSyntax SimplifiedLambdaExprSyntax::getBody()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Body).get()};
}

SimplifiedLambdaExprSyntax
SimplifiedLambdaExprSyntax::withFnToken(std::optional<TokenSyntax> fnToken)
{
   RefCountPtr<RawSyntax> fnTokenRaw;
   if (fnToken.has_value()) {
      fnTokenRaw = fnToken->getRaw();
   } else {
      fnTokenRaw = make_missing_token(T_FN);
   }
   return m_data->replaceChild<SimplifiedLambdaExprSyntax>(fnTokenRaw, Cursor::FnToken);
}

SimplifiedLambdaExprSyntax
SimplifiedLambdaExprSyntax::withReturnRefToken(std::optional<TokenSyntax> returnRefToken)
{
   RefCountPtr<RawSyntax> returnRefTokenRaw;
   if (returnRefToken.has_value()) {
      returnRefTokenRaw = returnRefToken->getRaw();
   } else {
      returnRefTokenRaw = nullptr;
   }
   return m_data->replaceChild<SimplifiedLambdaExprSyntax>(returnRefTokenRaw, Cursor::ReturnRefToken);
}

SimplifiedLambdaExprSyntax
SimplifiedLambdaExprSyntax::withParameterListClause(std::optional<ParameterClauseSyntax> parameterListClause)
{
   RefCountPtr<RawSyntax> parameterListClauseRaw;
   if (parameterListClause.has_value()) {
      parameterListClauseRaw = parameterListClause->getRaw();
   } else {
      parameterListClauseRaw = RawSyntax::missing(SyntaxKind::ParameterListClause);
   }
   return m_data->replaceChild<SimplifiedLambdaExprSyntax>(parameterListClauseRaw, Cursor::ParameterListClause);
}

SimplifiedLambdaExprSyntax
SimplifiedLambdaExprSyntax::withReturnType(std::optional<ReturnTypeClauseSyntax> returnType)
{
   RefCountPtr<RawSyntax> returnTypeRaw;
   if (returnType.has_value()) {
      returnTypeRaw = returnType->getRaw();
   } else {
      returnTypeRaw = nullptr;
   }
   return m_data->replaceChild<SimplifiedLambdaExprSyntax>(returnTypeRaw, Cursor::ReturnType);
}

SimplifiedLambdaExprSyntax
SimplifiedLambdaExprSyntax::withDoubleArrowToken(std::optional<TokenSyntax> doubleArrow)
{
   RefCountPtr<RawSyntax> doubleArrowRaw;
   if (doubleArrow.has_value()) {
      doubleArrowRaw = doubleArrow->getRaw();
   } else {
      doubleArrowRaw = make_missing_token(T_DOUBLE_ARROW);
   }
   return m_data->replaceChild<SimplifiedLambdaExprSyntax>(doubleArrowRaw, Cursor::DoubleArrowToken);
}

SimplifiedLambdaExprSyntax
SimplifiedLambdaExprSyntax::withBody(std::optional<ExprSyntax> body)
{
   RefCountPtr<RawSyntax> bodyRaw;
   if (body.has_value()) {
      bodyRaw = body->getRaw();
   } else {
      bodyRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<SimplifiedLambdaExprSyntax>(bodyRaw, Cursor::Body);
}

///
/// LambdaExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType LambdaExprSyntax::CHILD_NODE_CHOICES
{
   {
      LambdaExprSyntax::LambdaExpr, {
         SyntaxKind::ClassicLambdaExpr, SyntaxKind::SimplifiedLambdaExpr
      }
   }
};
#endif

void LambdaExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == SimplifiedLambdaExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, StaticToken, std::set{TokenKindType::T_STATIC});
   syntax_assert_child_kind(raw, LambdaExpr, CHILD_NODE_CHOICES.at(Cursor::LambdaExpr));
#endif
}

std::optional<TokenSyntax> LambdaExprSyntax::getStaticToken()
{
   RefCountPtr<SyntaxData> staticTokenData = m_data->getChild(Cursor::StaticToken);
   if (!staticTokenData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, staticTokenData.get()};
}

ExprSyntax LambdaExprSyntax::getLambdaExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::LambdaExpr).get()};
}

LambdaExprSyntax LambdaExprSyntax::withStaticToken(std::optional<TokenSyntax> staticToken)
{
   RefCountPtr<RawSyntax> staticTokenRaw;
   if (staticToken.has_value()) {
      staticTokenRaw = staticToken->getRaw();
   } else {
      staticTokenRaw = nullptr;
   }
   return m_data->replaceChild<LambdaExprSyntax>(staticTokenRaw, Cursor::StaticToken);
}

LambdaExprSyntax LambdaExprSyntax::withLambdaExpr(std::optional<ExprSyntax> lambdaExpr)
{
   RefCountPtr<RawSyntax> lambdaExprRaw;
   if (lambdaExpr.has_value()) {
      lambdaExprRaw = lambdaExpr->getRaw();
   } else {
      lambdaExprRaw = RawSyntax::missing(SyntaxKind::LambdaExpr);
   }
   return m_data->replaceChild<LambdaExprSyntax>(lambdaExprRaw, Cursor::LambdaExpr);
}

///
/// InstanceCreateExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType CHILD_NODE_CHOICES
{
   {
      InstanceCreateExprSyntax::CreateExpr, {
         SyntaxKind::AnonymousInstanceCreateExpr,
               SyntaxKind::SimpleInstanceCreateExpr
      }
   }
};
#endif

void InstanceCreateExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == InstanceCreateExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, CreateExpr, std::set{SyntaxKind::AnonymousClassDefinitionClause});
#endif
}

ExprSyntax InstanceCreateExprSyntax::getCreateExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::CreateExpr).get()};
}

InstanceCreateExprSyntax
InstanceCreateExprSyntax::withCreateExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::UnknownExpr);
   }
   return m_data->replaceChild<InstanceCreateExprSyntax>(exprRaw, Cursor::CreateExpr);
}

///
/// ScalarExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType ScalarExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      ScalarExprSyntax::Value, {
         TokenKindType::T_LNUMBER, TokenKindType::T_DNUMBER,
               TokenKindType::T_LINE, TokenKindType::T_FILE,
               TokenKindType::T_DIR, TokenKindType::T_TRAIT_CONST,
               TokenKindType::T_METHOD_CONST, TokenKindType::T_FUNC_CONST,
               TokenKindType::T_NS_CONST, TokenKindType::T_CLASS_CONST,
      }
   }
};
const NodeChoicesType ScalarExprSyntax::CHILD_NODE_CHOICES
{
   {
      ScalarExprSyntax::Value, {
         SyntaxKind::HeredocExpr, SyntaxKind::EncapsListStringExpr,
               SyntaxKind::DereferencableScalarExpr, SyntaxKind::ConstExpr
      }
   }
};
#endif

void ScalarExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ScalarExprSyntax::CHILDREN_COUNT);
   if (const RefCountPtr<RawSyntax> &valueChild = raw->getChild(Cursor::Value)) {
      if (valueChild->isToken()) {
         syntax_assert_child_token(raw, Value, CHILD_TOKEN_CHOICES.at(Cursor::Value));
      } else {
         syntax_assert_child_kind(raw, Value, CHILD_NODE_CHOICES.at(Cursor::Value));
      }
   }
#endif
}

Syntax ScalarExprSyntax::getValue()
{
   return Syntax {m_root, m_data->getChild(Cursor::Value).get()};
}

ScalarExprSyntax ScalarExprSyntax::withValue(std::optional<Syntax> value)
{
   RefCountPtr<RawSyntax> valueRaw;
   if (value.has_value()) {
      valueRaw = value->getRaw();
   } else {
      valueRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<ScalarExprSyntax>(valueRaw, Cursor::Value);
}

///
/// ClassRefParentExprSyntax
///
void ClassRefParentExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ClassRefParentExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, ParentKeyword, std::set{TokenKindType::T_CLASS_REF_PARENT});
#endif
}

TokenSyntax ClassRefParentExprSyntax::getParentKeyword()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::ParentKeyword).get()};
}

ClassRefParentExprSyntax ClassRefParentExprSyntax::withParentKeyword(std::optional<TokenSyntax> parentKeyword)
{
   RefCountPtr<RawSyntax> rawParentKeyword;
   if (parentKeyword.has_value()) {
      rawParentKeyword = parentKeyword->getRaw();
   } else {
      rawParentKeyword = RawSyntax::missing(TokenKindType::T_CLASS_REF_PARENT,
                                            OwnedString::makeUnowned(get_token_text(TokenKindType::T_CLASS_REF_PARENT)));
   }
   return m_data->replaceChild<ClassRefParentExprSyntax>(rawParentKeyword, Cursor::ParentKeyword);
}

void ClassRefSelfExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ClassRefSelfExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, SelfKeyword, std::set{TokenKindType::T_CLASS_REF_SELF});
#endif
}

TokenSyntax ClassRefSelfExprSyntax::getSelfKeyword()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::SelfKeyword).get()};
}

ClassRefSelfExprSyntax ClassRefSelfExprSyntax::withSelfKeyword(std::optional<TokenSyntax> selfKeyword)
{
   RefCountPtr<RawSyntax> rawSelfKeyword;
   if (selfKeyword.has_value()) {
      rawSelfKeyword = selfKeyword->getRaw();
   } else {
      rawSelfKeyword = RawSyntax::missing(TokenKindType::T_CLASS_REF_SELF,
                                          OwnedString::makeUnowned(get_token_text(TokenKindType::T_CLASS_REF_SELF)));
   }
   return m_data->replaceChild<ClassRefSelfExprSyntax>(rawSelfKeyword, Cursor::SelfKeyword);
}

void ClassRefStaticExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ClassRefStaticExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, StaticKeyword, std::set{TokenKindType::T_CLASS_REF_STATIC});
#endif
}

TokenSyntax ClassRefStaticExprSyntax::getStaticKeyword()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::StaticKeyword).get()};
}

ClassRefStaticExprSyntax ClassRefStaticExprSyntax::withStaticKeyword(std::optional<TokenSyntax> staticKeyword)
{
   RefCountPtr<RawSyntax> rawStaticKeyword;
   if (staticKeyword.has_value()) {
      rawStaticKeyword = staticKeyword->getRaw();
   } else {
      rawStaticKeyword = RawSyntax::missing(TokenKindType::T_CLASS_REF_STATIC,
                                            OwnedString::makeUnowned(get_token_text(TokenKindType::T_CLASS_REF_STATIC)));
   }
   return m_data->replaceChild<ClassRefStaticExprSyntax>(rawStaticKeyword, Cursor::StaticKeyword);
}

///
/// IntegerLiteralExprSyntax
///
void IntegerLiteralExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == IntegerLiteralExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, Digits, std::set{TokenKindType::T_LNUMBER});
#endif
}

TokenSyntax IntegerLiteralExprSyntax::getDigits()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::Digits).get()};
}

IntegerLiteralExprSyntax IntegerLiteralExprSyntax::withDigits(std::optional<TokenSyntax> digits)
{
   RefCountPtr<RawSyntax> rawDigits;
   if (digits.has_value()) {
      rawDigits = digits->getRaw();
   } else {
      rawDigits = RawSyntax::missing(TokenKindType::T_LNUMBER,
                                     OwnedString::makeUnowned(get_token_text(TokenKindType::T_LNUMBER)));
   }
   return m_data->replaceChild<IntegerLiteralExprSyntax>(rawDigits, Cursor::Digits);
}

///
/// FloatLiteralExprSyntax
///
void FloatLiteralExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == FloatLiteralExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, FloatDigits, std::set{TokenKindType::T_DNUMBER});
#endif
}

TokenSyntax FloatLiteralExprSyntax::getFloatDigits()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::FloatDigits).get()};
}

FloatLiteralExprSyntax FloatLiteralExprSyntax::withFloatDigits(std::optional<TokenSyntax> digits)
{
   RefCountPtr<RawSyntax> rawDigits;
   if (digits.has_value()) {
      rawDigits = digits->getRaw();
   } else {
      rawDigits = RawSyntax::missing(TokenKindType::T_DNUMBER,
                                     OwnedString::makeUnowned(get_token_text(TokenKindType::T_DNUMBER)));
   }
   return m_data->replaceChild<FloatLiteralExprSyntax>(rawDigits, Cursor::FloatDigits);
}

///
/// StringLiteralExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType StringLiteralExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      StringLiteralExprSyntax::LeftQuote, {
         TokenKindType::T_SINGLE_QUOTE, TokenKindType::T_DOUBLE_QUOTE
      }
   },
   {
      StringLiteralExprSyntax::RightQuote, {
         TokenKindType::T_SINGLE_QUOTE, TokenKindType::T_DOUBLE_QUOTE
      }
   }
};
#endif

void StringLiteralExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == StringLiteralExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, LeftQuote, CHILD_TOKEN_CHOICES.at(Cursor::LeftQuote));
   syntax_assert_child_token(raw, RightQuote, CHILD_TOKEN_CHOICES.at(Cursor::RightQuote));
   assert(raw->getChild(Cursor::LeftQuote)->getTokenKind() == raw->getChild(Cursor::RightQuote)->getTokenKind());
#endif
}

TokenSyntax StringLiteralExprSyntax::getLeftQuote()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftQuote).get()};
}

TokenSyntax StringLiteralExprSyntax::getText()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Text).get()};
}

TokenSyntax StringLiteralExprSyntax::getRightQuote()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightQuote).get()};
}

StringLiteralExprSyntax StringLiteralExprSyntax::withLeftQuote(std::optional<TokenSyntax> leftQuote)
{
   RefCountPtr<RawSyntax> leftQuoteRaw;
   if (leftQuote.has_value()) {
      leftQuoteRaw = leftQuote->getRaw();
   } else {
      leftQuoteRaw = RawSyntax::missing(TokenKindType::T_DOUBLE_QUOTE,
                                        OwnedString::makeUnowned(get_token_text(TokenKindType::T_DOUBLE_QUOTE)));
   }
   return m_data->replaceChild<StringLiteralExprSyntax>(leftQuoteRaw, Cursor::LeftQuote);
}

StringLiteralExprSyntax StringLiteralExprSyntax::withText(std::optional<TokenSyntax> text)
{
   RefCountPtr<RawSyntax> textRaw;
   if (text.has_value()) {
      textRaw = text->getRaw();
   } else {
      textRaw = RawSyntax::missing(TokenKindType::T_CONSTANT_ENCAPSED_STRING,
                                   OwnedString::makeUnowned(get_token_text(TokenKindType::T_CONSTANT_ENCAPSED_STRING)));
   }
   return m_data->replaceChild<StringLiteralExprSyntax>(textRaw, Cursor::Text);
}

StringLiteralExprSyntax StringLiteralExprSyntax::withRightQuote(std::optional<TokenSyntax> rightQuote)
{
   RefCountPtr<RawSyntax> rightQuoteRaw;
   if (rightQuote.has_value()) {
      rightQuoteRaw = rightQuote->getRaw();
   } else {
      RefCountPtr<RawSyntax> leftQuote = getRaw()->getChild(Cursor::LeftQuote);
      if (leftQuote) {
         TokenKindType leftQuoteKind = leftQuote->getTokenKind();
         rightQuoteRaw = RawSyntax::missing(leftQuoteKind,
                                            OwnedString::makeUnowned(get_token_text(leftQuoteKind)));
      } else {
         rightQuoteRaw = RawSyntax::missing(TokenKindType::T_DOUBLE_QUOTE,
                                            OwnedString::makeUnowned(get_token_text(TokenKindType::T_DOUBLE_QUOTE)));
      }
   }
   return m_data->replaceChild<StringLiteralExprSyntax>(rightQuoteRaw, Cursor::LeftQuote);
}

///
/// BooleanLiteralExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType BooleanLiteralExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      BooleanLiteralExprSyntax::Boolean, {
         TokenKindType::T_FALSE,
               TokenKindType::T_TRUE
      }
   }
};
#endif

void BooleanLiteralExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == BooleanLiteralExprSyntax::CHILDREN_COUNT);
   ///
   /// check Boolean token choice
   ///
   syntax_assert_child_token(raw, Boolean, CHILD_TOKEN_CHOICES.at(Boolean));
#endif
}

TokenSyntax BooleanLiteralExprSyntax::getBooleanValue()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::Boolean).get()};
}

BooleanLiteralExprSyntax BooleanLiteralExprSyntax::withBooleanValue(std::optional<TokenSyntax> booleanValue)
{
   RefCountPtr<RawSyntax> rawBooleanValue;
   if (booleanValue.has_value()) {
      rawBooleanValue = booleanValue->getRaw();
   } else {
      rawBooleanValue = RawSyntax::missing(TokenKindType::T_TRUE,
                                           OwnedString::makeUnowned(get_token_text(TokenKindType::T_TRUE)));
   }
   return m_data->replaceChild<BooleanLiteralExprSyntax>(rawBooleanValue, Cursor::Boolean);
}

///
/// IssetVariableSyntax
///
void IssetVariableSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == IssetVariableSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Expr, std::set{SyntaxKind::Expr});
#endif
}

ExprSyntax IssetVariableSyntax::getExpr()
{
   return ExprSyntax{m_root, m_data->getChild(Cursor::Expr).get()};
}

IssetVariableSyntax IssetVariableSyntax::withExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<IssetVariableSyntax>(exprRaw, Cursor::Expr);
}

///
/// IssetVariableListItemSyntax
///
void IssetVariableListItemSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == IssetVariableListItemSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, CommaToken, std::set{TokenKindType::T_COMMA});
   syntax_assert_child_kind(raw, Variable, std::set{SyntaxKind::IssetVariable});
#endif
}

std::optional<TokenSyntax> IssetVariableListItemSyntax::getComma()
{
   RefCountPtr<SyntaxData> commaData = m_data->getChild(Cursor::CommaToken);
   if (!commaData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, commaData.get()};
}

IssetVariableSyntax IssetVariableListItemSyntax::getVariable()
{
   return IssetVariableSyntax {m_root, m_data->getChild(Cursor::Variable).get()};
}

IssetVariableListItemSyntax IssetVariableListItemSyntax::withComma(std::optional<TokenSyntax> comma)
{
   RefCountPtr<RawSyntax> commaRaw;
   if (comma.has_value()) {
      commaRaw = comma->getRaw();
   } else {
      commaRaw = make_missing_token(T_COMMA);
   }
   return m_data->replaceChild<IssetVariableListItemSyntax>(commaRaw, Cursor::CommaToken);
}


IssetVariableListItemSyntax IssetVariableListItemSyntax::withVariable(std::optional<IssetVariableSyntax> variable)
{
   RefCountPtr<RawSyntax> variableRaw;
   if (variable.has_value()) {
      variableRaw = variable->getRaw();
   } else {
      variableRaw = RawSyntax::missing(SyntaxKind::IssetVariable);
   }
   return m_data->replaceChild<IssetVariableListItemSyntax>(variableRaw, Cursor::Variable);
}

///
/// IssetVariablesClauseSyntax
///
void IssetVariablesClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == IssetVariableListItemSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, LeftParenToken, std::set{TokenKindType::T_LEFT_PAREN});
   syntax_assert_child_kind(raw, IsSetVariablesList, std::set{SyntaxKind::IssetVariablesList});
   syntax_assert_child_token(raw, RightParenToken, std::set{TokenKindType::T_RIGHT_PAREN});
#endif
}

TokenSyntax IssetVariablesClauseSyntax::getLeftParenToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftParenToken).get()};
}

IssetVariablesListSyntax IssetVariablesClauseSyntax::getIsSetVariablesList()
{
   return IssetVariablesListSyntax {m_root, m_data->getChild(Cursor::IsSetVariablesList).get()};
}

TokenSyntax IssetVariablesClauseSyntax::getRightParenToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightParenToken).get()};
}

IssetVariablesClauseSyntax
IssetVariablesClauseSyntax::withLeftParenToken(std::optional<TokenSyntax> leftParenToken)
{
   RefCountPtr<RawSyntax> leftParenTokenRaw;
   if (leftParenToken.has_value()) {
      leftParenTokenRaw = leftParenToken->getRaw();
   } else {
      leftParenTokenRaw = make_missing_token(T_LEFT_PAREN);
   }
   return m_data->replaceChild<IssetVariablesClauseSyntax>(leftParenTokenRaw, Cursor::LeftParenToken);
}

IssetVariablesClauseSyntax
IssetVariablesClauseSyntax::withIsSetVariablesList(std::optional<IssetVariablesListSyntax> issetVariablesList)
{
   RefCountPtr<RawSyntax> issetVariablesListRaw;
   if (issetVariablesList.has_value()) {
      issetVariablesListRaw = issetVariablesList->getRaw();
   } else {
      issetVariablesListRaw = RawSyntax::missing(SyntaxKind::IssetVariablesList);
   }
   return m_data->replaceChild<IssetVariablesClauseSyntax>(issetVariablesListRaw, Cursor::IsSetVariablesList);
}

IssetVariablesClauseSyntax
IssetVariablesClauseSyntax::withRightParenToken(std::optional<TokenSyntax> rightParenToken)
{
   RefCountPtr<RawSyntax> rightParenTokenRaw;
   if (rightParenToken.has_value()) {
      rightParenTokenRaw = rightParenToken->getRaw();
   } else {
      rightParenTokenRaw = make_missing_token(T_RIGHT_PAREN);
   }
   return m_data->replaceChild<IssetVariablesClauseSyntax>(rightParenTokenRaw, Cursor::RightParenToken);
}

///
/// IssetFuncExprSyntax
///
void IssetFuncExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == IssetFuncExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, IssetToken, std::set{TokenKindType::T_ISSET});
   syntax_assert_child_kind(raw, IssetVariablesClause, std::set{SyntaxKind::IssetVariablesClause});
#endif
}

TokenSyntax IssetFuncExprSyntax::getIssetToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::IssetToken).get()};
}

IssetVariablesClauseSyntax IssetFuncExprSyntax::getIssetVariablesClause()
{
   return IssetVariablesClauseSyntax {m_root, m_data->getChild(Cursor::IssetVariablesClause).get()};
}

IssetFuncExprSyntax
IssetFuncExprSyntax::withIssetToken(std::optional<TokenSyntax> issetToken)
{
   RefCountPtr<RawSyntax> issetTokenRaw;
   if (issetToken.has_value()) {
      issetTokenRaw = issetToken->getRaw();
   } else {
      issetTokenRaw = make_missing_token(T_ISSET);
   }
   return m_data->replaceChild<IssetFuncExprSyntax>(issetTokenRaw, Cursor::IssetToken);
}

IssetFuncExprSyntax
IssetFuncExprSyntax::withIssetVariablesClause(std::optional<IssetVariablesClauseSyntax> isSetVariablesClause)
{
   RefCountPtr<RawSyntax> isSetVariablesClauseRaw;
   if (isSetVariablesClause.has_value()) {
      isSetVariablesClauseRaw = isSetVariablesClause->getRaw();
   } else {
      isSetVariablesClauseRaw = RawSyntax::missing(SyntaxKind::IssetVariablesClause);
   }
   return m_data->replaceChild<IssetFuncExprSyntax>(isSetVariablesClauseRaw, Cursor::IssetVariablesClause);
}

///
/// EmptyFuncExprSyntax
///
void EmptyFuncExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EmptyFuncExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, EmptyToken, std::set{TokenKindType::T_EMPTY});
   syntax_assert_child_kind(raw, ArgumentsClause, std::set{SyntaxKind::ParenDecoratedExpr});
#endif
}

TokenSyntax EmptyFuncExprSyntax::getEmptyToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::EmptyToken).get()};
}

ParenDecoratedExprSyntax
EmptyFuncExprSyntax::getArgumentsClause()
{
   return ParenDecoratedExprSyntax {m_root, m_data->getChild(Cursor::ArgumentsClause).get()};
}

EmptyFuncExprSyntax
EmptyFuncExprSyntax::withEmptyToken(std::optional<TokenSyntax> emptyToken)
{
   RefCountPtr<RawSyntax> emptyTokenRaw;
   if (emptyToken.has_value()) {
      emptyTokenRaw = emptyToken->getRaw();
   } else {
      emptyTokenRaw = make_missing_token(T_EMPTY);
   }
   return m_data->replaceChild<EmptyFuncExprSyntax>(emptyTokenRaw, Cursor::EmptyToken);
}

EmptyFuncExprSyntax
EmptyFuncExprSyntax::withArgumentsClause(std::optional<ParenDecoratedExprSyntax> argumentsClause)
{
   RefCountPtr<RawSyntax> argumentsClauseRaw;
   if (argumentsClause.has_value()) {
      argumentsClauseRaw = argumentsClause->getRaw();
   } else {
      argumentsClauseRaw = RawSyntax::missing(SyntaxKind::ArgumentListClause);
   }
   return m_data->replaceChild<EmptyFuncExprSyntax>(argumentsClauseRaw, Cursor::ArgumentsClause);
}

///
/// IncludeExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType IncludeExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      IncludeExprSyntax::IncludeToken, {
         TokenKindType::T_INCLUDE, TokenKindType::T_INCLUDE_ONCE,
      }
   }
};
#endif

void IncludeExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == IncludeExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, IncludeToken, CHILD_TOKEN_CHOICES.at(Cursor::IncludeToken));
   syntax_assert_child_kind(raw, ArgExpr, std::set{SyntaxKind::Expr});
#endif
}

TokenSyntax IncludeExprSyntax::getIncludeToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::IncludeToken).get()};
}

ExprSyntax IncludeExprSyntax::getArgExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::ArgExpr).get()};
}

IncludeExprSyntax IncludeExprSyntax::withIncludeToken(std::optional<TokenSyntax> includeToken)
{
   RefCountPtr<RawSyntax> includeTokenRaw;
   if (includeToken.has_value()) {
      includeTokenRaw = includeToken->getRaw();
   } else {
      includeTokenRaw = make_missing_token(T_INCLUDE);
   }
   return m_data->replaceChild<IncludeExprSyntax>(includeTokenRaw, Cursor::IncludeToken);
}

IncludeExprSyntax IncludeExprSyntax::withArgExpr(std::optional<ExprSyntax> argExpr)
{
   RefCountPtr<RawSyntax> argExprRaw;
   if (argExpr.has_value()) {
      argExprRaw = argExpr->getRaw();
   } else {
      argExprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<IncludeExprSyntax>(argExprRaw, Cursor::ArgExpr);
}

///
/// IncludeExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType RequireExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      RequireExprSyntax::RequireToken, {
         TokenKindType::T_REQUIRE, TokenKindType::T_REQUIRE_ONCE,
      }
   }
};
#endif

void RequireExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == RequireExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, RequireToken, CHILD_TOKEN_CHOICES.at(Cursor::RequireToken));
   syntax_assert_child_kind(raw, ArgExpr, std::set{SyntaxKind::Expr});
#endif
}

TokenSyntax RequireExprSyntax::getRequireToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RequireToken).get()};
}

ExprSyntax RequireExprSyntax::getArgExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::ArgExpr).get()};
}

RequireExprSyntax
RequireExprSyntax::withRequireToken(std::optional<TokenSyntax> requireToken)
{
   RefCountPtr<RawSyntax> requireTokenRaw;
   if (requireToken.has_value()) {
      requireTokenRaw = requireToken->getRaw();
   } else {
      requireTokenRaw = make_missing_token(T_REQUIRE);
   }
   return m_data->replaceChild<RequireExprSyntax>(requireTokenRaw, Cursor::RequireToken);
}

RequireExprSyntax
RequireExprSyntax::withArgExpr(std::optional<ExprSyntax> argExpr)
{
   RefCountPtr<RawSyntax> argExprRaw;
   if (argExpr.has_value()) {
      argExprRaw = argExpr->getRaw();
   } else {
      argExprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<RequireExprSyntax>(argExprRaw, Cursor::ArgExpr);
}

///
/// EmptyFuncExprSyntax
///
void EvalFuncExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EmptyFuncExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, EvalToken, std::set{TokenKindType::T_EVAL});
   syntax_assert_child_kind(raw, ArgumentsClause, std::set{SyntaxKind::ParenDecoratedExpr});
#endif
}

TokenSyntax EvalFuncExprSyntax::getEvalToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::EvalToken).get()};
}

ParenDecoratedExprSyntax EvalFuncExprSyntax::getArgumentsClause()
{
   return ParenDecoratedExprSyntax{m_root, m_data->getChild(Cursor::ArgumentsClause).get()};
}

EvalFuncExprSyntax
EvalFuncExprSyntax::withEvalToken(std::optional<TokenSyntax> evalToken)
{
   RefCountPtr<RawSyntax> evalTokenRaw;
   if (evalToken.has_value()) {
      evalTokenRaw = evalToken->getRaw();
   } else {
      evalTokenRaw = make_missing_token(T_EVAL);
   }
   return m_data->replaceChild<EvalFuncExprSyntax>(evalTokenRaw, Cursor::EvalToken);
}

EvalFuncExprSyntax
EvalFuncExprSyntax::withArgumentsClause(std::optional<ParenDecoratedExprSyntax> argumentsClause)
{
   RefCountPtr<RawSyntax> argumentsClauseRaw;
   if (argumentsClause.has_value()) {
      argumentsClauseRaw = argumentsClause->getRaw();
   } else {
      argumentsClauseRaw = RawSyntax::missing(SyntaxKind::ArgumentListClause);
   }
   return m_data->replaceChild<EvalFuncExprSyntax>(argumentsClauseRaw, Cursor::ArgumentsClause);
}

///
/// PrintFuncExprSyntax
///
void PrintFuncExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == PrintFuncExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, PrintToken, std::set{TokenKindType::T_PRINT});
   syntax_assert_child_kind(raw, ArgsExpr, std::set{SyntaxKind::Expr});
#endif
}

TokenSyntax PrintFuncExprSyntax::getPrintToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::PrintToken).get()};
}

ExprSyntax PrintFuncExprSyntax::getArgsExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::ArgsExpr).get()};
}

PrintFuncExprSyntax PrintFuncExprSyntax::withPrintToken(std::optional<TokenSyntax> printToken)
{
   RefCountPtr<RawSyntax> printTokenRaw;
   if (printToken.has_value()) {
      printTokenRaw = printToken->getRaw();
   } else {
      printTokenRaw = make_missing_token(T_PRINT);
   }
   return m_data->replaceChild<PrintFuncExprSyntax>(printTokenRaw, Cursor::PrintToken);
}

PrintFuncExprSyntax PrintFuncExprSyntax::withArgsExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<PrintFuncExprSyntax>(exprRaw, Cursor::ArgsExpr);
}

///
/// FuncLikeExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType FuncLikeExprSyntax::CHILD_NODE_CHOICES
{
   {
      FuncLikeExprSyntax::FuncLikeExpr, {
         SyntaxKind::IssetFuncExpr, SyntaxKind::EmptyFuncExpr,
               SyntaxKind::IncludeExpr, SyntaxKind::RequireExpr,
               SyntaxKind::EvalFuncExpr,
      }
   }
};
#endif

void FuncLikeExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == FuncLikeExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, FuncLikeExpr, CHILD_NODE_CHOICES.at(Cursor::FuncLikeExpr));
#endif
}

ExprSyntax FuncLikeExprSyntax::getFuncLikeExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::FuncLikeExpr).get()};
}

FuncLikeExprSyntax
FuncLikeExprSyntax::withFuncLikeExpr(std::optional<ExprSyntax> funcLikeExpr)
{
   RefCountPtr<RawSyntax> FuncLikeExprSyntaxRaw;
   if (funcLikeExpr.has_value()) {
      FuncLikeExprSyntaxRaw = funcLikeExpr->getRaw();
   } else {
      FuncLikeExprSyntaxRaw = RawSyntax::missing(SyntaxKind::UnknownExpr);
   }
   return m_data->replaceChild<FuncLikeExprSyntax>(FuncLikeExprSyntaxRaw, Cursor::FuncLikeExpr);
}

///
/// ArrayStructureAssignmentExprSyntax
///

void ArrayStructureAssignmentExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ArrayStructureAssignmentExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, ArrayStructure, std::set{SyntaxKind::SimplifiedArrayCreateExpr});
   syntax_assert_child_token(raw, EqualToken, std::set{TokenKindType::T_EQUAL});
   syntax_assert_child_kind(raw, ValueExpr, std::set{SyntaxKind::Expr});
#endif
}

SimplifiedArrayCreateExprSyntax ArrayStructureAssignmentExprSyntax::getArrayStructure()
{
   return SimplifiedArrayCreateExprSyntax {m_root, m_data->getChild(Cursor::ArrayStructure).get()};
}

TokenSyntax ArrayStructureAssignmentExprSyntax::getEqualToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::EqualToken).get()};
}

ExprSyntax ArrayStructureAssignmentExprSyntax::getValueExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::ValueExpr).get()};
}

ArrayStructureAssignmentExprSyntax
ArrayStructureAssignmentExprSyntax::withArrayStructure(std::optional<SimplifiedArrayCreateExprSyntax> arrayStructure)
{
   RefCountPtr<RawSyntax> arrayStructureRaw;
   if (arrayStructure.has_value()) {
      arrayStructureRaw = arrayStructure->getRaw();
   } else {
      arrayStructureRaw = RawSyntax::missing(SyntaxKind::SimplifiedArrayCreateExpr);
   }
   return m_data->replaceChild<ArrayStructureAssignmentExprSyntax>(arrayStructureRaw, Cursor::ArrayStructure);
}

ArrayStructureAssignmentExprSyntax
ArrayStructureAssignmentExprSyntax::withEqualToken(std::optional<TokenSyntax> equalToken)
{
   RefCountPtr<RawSyntax> equalTokenRaw;
   if (equalToken.has_value()) {
      equalTokenRaw = equalToken->getRaw();
   } else {
      equalTokenRaw = make_missing_token(T_EQUAL);
   }
   return m_data->replaceChild<ArrayStructureAssignmentExprSyntax>(equalTokenRaw, Cursor::EqualToken);
}

ArrayStructureAssignmentExprSyntax
ArrayStructureAssignmentExprSyntax::withValueExpr(std::optional<ExprSyntax> valueExpr)
{
   RefCountPtr<RawSyntax> valueExprRaw;
   if (valueExpr.has_value()) {
      valueExprRaw = valueExpr->getRaw();
   } else {
      valueExprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<ArrayStructureAssignmentExprSyntax>(valueExprRaw, Cursor::ValueExpr);
}

///
/// ListStructureClauseSyntax
///
void ListStructureClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ListStructureClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, ListToken, std::set{TokenKindType::T_LIST});
   syntax_assert_child_token(raw, LeftParen, std::set{TokenKindType::T_LEFT_PAREN});
   syntax_assert_child_token(raw, RightParen, std::set{TokenKindType::T_RIGHT_PAREN});
   syntax_assert_child_kind(raw, PairItemList, std::set{SyntaxKind::ArrayPairList});
#endif
}

TokenSyntax ListStructureClauseSyntax::getListToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::ListToken).get()};
}

TokenSyntax ListStructureClauseSyntax::getLeftParen()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftParen).get()};
}

ArrayPairListSyntax ListStructureClauseSyntax::getPairItemList()
{
   return ArrayPairListSyntax {m_root, m_data->getChild(Cursor::PairItemList).get()};
}

TokenSyntax ListStructureClauseSyntax::getRightParen()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightParen).get()};
}

ListStructureClauseSyntax
ListStructureClauseSyntax::withListToken(std::optional<TokenSyntax> listToken)
{
   RefCountPtr<RawSyntax> listTokenRaw;
   if (listToken.has_value()) {
      listTokenRaw = listToken->getRaw();
   } else {
      listTokenRaw = make_missing_token(T_LIST);
   }
   return m_data->replaceChild<ListStructureClauseSyntax>(listTokenRaw, Cursor::ListToken);
}

ListStructureClauseSyntax
ListStructureClauseSyntax::withLeftParen(std::optional<TokenSyntax> leftParen)
{
   RefCountPtr<RawSyntax> leftParanRaw;
   if (leftParen.has_value()) {
      leftParanRaw = leftParen->getRaw();
   } else {
      leftParanRaw = make_missing_token(T_LEFT_PAREN);
   }
   return m_data->replaceChild<ListStructureClauseSyntax>(leftParanRaw, Cursor::LeftParen);
}

ListStructureClauseSyntax
ListStructureClauseSyntax::withPairItemList(std::optional<ArrayPairListSyntax> pairItemList)
{
   RefCountPtr<RawSyntax> pairItemListRaw;
   if (pairItemList.has_value()) {
      pairItemListRaw = pairItemList->getRaw();
   } else {
      pairItemListRaw = RawSyntax::missing(SyntaxKind::ArrayPairList);
   }
   return m_data->replaceChild<ListStructureClauseSyntax>(pairItemListRaw, Cursor::PairItemList);
}

ListStructureClauseSyntax
ListStructureClauseSyntax::withRightParen(std::optional<TokenSyntax> rightParen)
{
   RefCountPtr<RawSyntax> rightParenRaw;
   if (rightParen.has_value()) {
      rightParenRaw = rightParen->getRaw();
   } else {
      rightParenRaw = make_missing_token(T_RIGHT_PAREN);
   }
   return m_data->replaceChild<ListStructureClauseSyntax>(rightParenRaw, Cursor::RightParen);
}

///
/// ListStructureAssignmentExprSyntax
///
void ListStructureAssignmentExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ListStructureClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, ListStrcuture, std::set{SyntaxKind::ListStructureClause});
   syntax_assert_child_token(raw, EqualToken, std::set{TokenKindType::T_EQUAL});
   syntax_assert_child_kind(raw, ValueExpr, std::set{SyntaxKind::Expr});
#endif
}

ListStructureClauseSyntax ListStructureAssignmentExprSyntax::getListStrcuture()
{
   return ListStructureClauseSyntax{m_root, m_data->getChild(Cursor::ListStrcuture).get()};
}

TokenSyntax ListStructureAssignmentExprSyntax::getEqualToken()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::EqualToken).get()};
}

ExprSyntax ListStructureAssignmentExprSyntax::getValueExpr()
{
   return ExprSyntax{m_root, m_data->getChild(Cursor::ValueExpr).get()};
}

ListStructureAssignmentExprSyntax
ListStructureAssignmentExprSyntax::withListStrcuture(std::optional<ListStructureClauseSyntax> listStructure)
{
   RefCountPtr<RawSyntax> rawListStructure;
   if (listStructure.has_value()) {
      rawListStructure = listStructure->getRaw();
   } else {
      rawListStructure = RawSyntax::missing(SyntaxKind::ListStructureClause);
   }
   return m_data->replaceChild<ListStructureAssignmentExprSyntax>(rawListStructure, Cursor::ListStrcuture);
}

ListStructureAssignmentExprSyntax
ListStructureAssignmentExprSyntax::withEqualToken(std::optional<TokenSyntax> equalToken)
{
   RefCountPtr<RawSyntax> rawEqualToken;
   if (equalToken.has_value()) {
      rawEqualToken = equalToken->getRaw();
   } else {
      rawEqualToken = make_missing_token(T_EQUAL);
   }
   return m_data->replaceChild<ListStructureAssignmentExprSyntax>(rawEqualToken, Cursor::EqualToken);
}

ListStructureAssignmentExprSyntax
ListStructureAssignmentExprSyntax::withValueExpr(std::optional<ExprSyntax> valueExpr)
{
   RefCountPtr<RawSyntax> rawValueExpr;
   if (valueExpr.has_value()) {
      rawValueExpr = valueExpr->getRaw();
   } else {
      rawValueExpr = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<ListStructureAssignmentExprSyntax>(rawValueExpr, Cursor::ValueExpr);
}

///
/// assignmentexprExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType AssignmentExprSyntax::CHILD_NODE_CHOICES
{
   {
      AssignmentExprSyntax::ValueExpr, {
         SyntaxKind::ReferencedVariableExpr, SyntaxKind::VariableExpr,
      }
   }
};
#endif

void AssignmentExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == AssignmentExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Target, std::set{SyntaxKind::VariableExpr});
   syntax_assert_child_token(raw, AssignToken, std::set{TokenKindType::T_EQUAL});
   syntax_assert_child_kind(raw, ValueExpr, CHILD_NODE_CHOICES.at(Cursor::ValueExpr));
#endif
}

VariableExprSyntax AssignmentExprSyntax::getTarget()
{
   return VariableExprSyntax {m_root, m_data->getChild(Cursor::Target).get()};
}

ExprSyntax AssignmentExprSyntax::getValueExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::ValueExpr).get()};
}

AssignmentExprSyntax AssignmentExprSyntax::withTarget(std::optional<VariableExprSyntax> target)
{
   RefCountPtr<RawSyntax> targetRaw;
   if (target.has_value()) {
      targetRaw = target->getRaw();
   } else {
      targetRaw = RawSyntax::missing(SyntaxKind::VariableExpr);
   }
   return m_data->replaceChild<AssignmentExprSyntax>(targetRaw, Cursor::Target);
}

AssignmentExprSyntax AssignmentExprSyntax::withAssignToken(std::optional<TokenSyntax> assignToken)
{
   RefCountPtr<RawSyntax> assignTokenRaw;
   if (assignToken.has_value()) {
      assignTokenRaw = assignToken->getRaw();
   } else {
      assignTokenRaw = make_missing_token(T_EQUAL);
   }
   return m_data->replaceChild<AssignmentExprSyntax>(assignTokenRaw, Cursor::AssignToken);
}

AssignmentExprSyntax AssignmentExprSyntax::withValueExpr(std::optional<ExprSyntax> valueExpr)
{
   RefCountPtr<RawSyntax> valueExprRaw;
   if (valueExpr.has_value()) {
      valueExprRaw = valueExpr->getRaw();
   } else {
      valueExprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<AssignmentExprSyntax>(valueExprRaw, Cursor::ValueExpr);
}

///
/// CompoundAssignmentExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType CompoundAssignmentExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      CompoundAssignmentExprSyntax::CompoundAssignToken, {
         TokenKindType::T_PLUS_EQUAL, TokenKindType::T_MINUS_EQUAL,
               TokenKindType::T_MUL_EQUAL, TokenKindType::T_POW_EQUAL,
               TokenKindType::T_DIV_EQUAL, TokenKindType::T_STR_CONCAT_EQUAL,
               TokenKindType::T_MOD_EQUAL, TokenKindType::T_AND_EQUAL,
               TokenKindType::T_OR_EQUAL, TokenKindType::T_XOR_EQUAL,
               TokenKindType::T_SL_EQUAL, TokenKindType::T_SR_EQUAL,
               TokenKindType::T_COALESCE_EQUAL
      }
   }
};
#endif

void CompoundAssignmentExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == CompoundAssignmentExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Target, std::set{SyntaxKind::VariableExpr});
   syntax_assert_child_token(raw, CompoundAssignToken, CHILD_TOKEN_CHOICES.at(Cursor::CompoundAssignToken));
   syntax_assert_child_kind(raw, ValueExpr, std::set{SyntaxKind::Expr});
#endif
}

VariableExprSyntax CompoundAssignmentExprSyntax::getTarget()
{
   return VariableExprSyntax {m_root, m_data->getChild(Cursor::Target).get()};
}

TokenSyntax CompoundAssignmentExprSyntax::getCompoundAssignToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::CompoundAssignToken).get()};
}

ExprSyntax CompoundAssignmentExprSyntax::getValueExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::ValueExpr).get()};
}

CompoundAssignmentExprSyntax
CompoundAssignmentExprSyntax::withTarget(std::optional<VariableExprSyntax> target)
{
   RefCountPtr<RawSyntax> targetRaw;
   if (target.has_value()) {
      targetRaw = target->getRaw();
   } else {
      targetRaw = RawSyntax::missing(SyntaxKind::VariableExpr);
   }
   return m_data->replaceChild<CompoundAssignmentExprSyntax>(targetRaw, Cursor::Target);
}

CompoundAssignmentExprSyntax
CompoundAssignmentExprSyntax::withCompoundAssignToken(std::optional<TokenSyntax> compoundAssignToken)
{
   RefCountPtr<RawSyntax> compoundAssignTokenRaw;
   if (compoundAssignToken.has_value()) {
      compoundAssignTokenRaw = compoundAssignToken->getRaw();
   } else {
      compoundAssignTokenRaw = make_missing_token(T_PLUS_EQUAL);
   }
   return m_data->replaceChild<CompoundAssignmentExprSyntax>(compoundAssignTokenRaw, Cursor::CompoundAssignToken);
}

CompoundAssignmentExprSyntax
CompoundAssignmentExprSyntax::withValueExpr(std::optional<ExprSyntax> valueExpr)
{
   RefCountPtr<RawSyntax> valueExprRaw;
   if (valueExpr.has_value()) {
      valueExprRaw = valueExpr->getRaw();
   } else {
      valueExprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<CompoundAssignmentExprSyntax>(valueExprRaw, Cursor::ValueExpr);
}

///
/// LogicalExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType LogicalExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      LogicalExprSyntax::LogicalOperator, {
         TokenKindType::T_BOOLEAN_OR, TokenKindType::T_BOOLEAN_AND,
               TokenKindType::T_LOGICAL_OR, TokenKindType::T_LOGICAL_AND,
               TokenKindType::T_LOGICAL_OR, TokenKindType::T_LOGICAL_XOR,
      }
   }
};
#endif

void LogicalExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == LogicalExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Lhs, std::set{SyntaxKind::Expr});
   syntax_assert_child_token(raw, LogicalOperator, CHILD_TOKEN_CHOICES.at(Cursor::LogicalOperator));
   syntax_assert_child_kind(raw, Rhs, std::set{SyntaxKind::Expr});
#endif
}

ExprSyntax LogicalExprSyntax::getLhs()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Lhs).get()};
}

TokenSyntax LogicalExprSyntax::getLogicalOperator()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LogicalOperator).get()};
}

ExprSyntax LogicalExprSyntax::getRhs()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Rhs).get()};
}

LogicalExprSyntax LogicalExprSyntax::withLhs(std::optional<ExprSyntax> lhs)
{
   RefCountPtr<RawSyntax> lhsRaw;
   if (lhs.has_value()) {
      lhsRaw = lhs->getRaw();
   } else {
      lhsRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<LogicalExprSyntax>(lhsRaw, Cursor::Lhs);
}

LogicalExprSyntax
LogicalExprSyntax::withLogicalOperator(std::optional<TokenSyntax> logicalOperator)
{
   RefCountPtr<RawSyntax> logicalOperatorRaw;
   if (logicalOperator.has_value()) {
      logicalOperatorRaw = logicalOperator->getRaw();
   } else {
      logicalOperatorRaw = make_missing_token(T_BOOLEAN_AND);
   }
   return m_data->replaceChild<LogicalExprSyntax>(logicalOperatorRaw, Cursor::LogicalOperator);
}

LogicalExprSyntax
LogicalExprSyntax::withRhs(std::optional<ExprSyntax> rhs)
{
   RefCountPtr<RawSyntax> rhsRaw;
   if (rhs.has_value()) {
      rhsRaw = rhs->getRaw();
   } else {
      rhsRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<LogicalExprSyntax>(rhsRaw, Cursor::Rhs);
}

///
/// BitLogicalExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType BitLogicalExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      BitLogicalExprSyntax::BitLogicalOperator, {
         TokenKindType::T_VBAR, TokenKindType::T_AMPERSAND,
               TokenKindType::T_CARET, TokenKindType::T_LOGICAL_AND,
               TokenKindType::T_LOGICAL_XOR,
      }
   }
};
#endif

void BitLogicalExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == BitLogicalExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Lhs, std::set{SyntaxKind::Expr});
   syntax_assert_child_token(raw, BitLogicalOperator, CHILD_TOKEN_CHOICES.at(Cursor::BitLogicalOperator));
   syntax_assert_child_kind(raw, Rhs, std::set{SyntaxKind::Expr});
#endif
}

ExprSyntax BitLogicalExprSyntax::getLhs()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Lhs).get()};
}

TokenSyntax BitLogicalExprSyntax::getBitLogicalOperator()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::BitLogicalOperator).get()};
}

ExprSyntax BitLogicalExprSyntax::getRhs()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Rhs).get()};
}

BitLogicalExprSyntax BitLogicalExprSyntax::withLhs(std::optional<ExprSyntax> lhs)
{
   RefCountPtr<RawSyntax> lhsRaw;
   if (lhs.has_value()) {
      lhsRaw = lhs->getRaw();
   } else {
      lhsRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<BitLogicalExprSyntax>(lhsRaw, Cursor::Lhs);
}

BitLogicalExprSyntax
BitLogicalExprSyntax::withBitLogicalOperator(std::optional<TokenSyntax> bitLogicalOperator)
{
   RefCountPtr<RawSyntax> bitLogicalOperatorRaw;
   if (bitLogicalOperator.has_value()) {
      bitLogicalOperatorRaw = bitLogicalOperator->getRaw();
   } else {
      bitLogicalOperatorRaw = make_missing_token(T_AMPERSAND);
   }
   return m_data->replaceChild<BitLogicalExprSyntax>(bitLogicalOperatorRaw, Cursor::BitLogicalOperator);
}

BitLogicalExprSyntax
BitLogicalExprSyntax::withRhs(std::optional<ExprSyntax> rhs)
{
   RefCountPtr<RawSyntax> rhsRaw;
   if (rhs.has_value()) {
      rhsRaw = rhs->getRaw();
   } else {
      rhsRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<BitLogicalExprSyntax>(rhsRaw, Cursor::Rhs);
}

///
/// RelationExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType RelationExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      RelationExprSyntax::RelationOperator, {
         TokenKindType::T_IS_IDENTICAL, TokenKindType::T_IS_NOT_IDENTICAL,
               TokenKindType::T_IS_EQUAL, TokenKindType::T_IS_NOT_EQUAL,
               TokenKindType::T_LEFT_ANGLE, TokenKindType::T_IS_SMALLER_OR_EQUAL,
               TokenKindType::T_RIGHT_ANGLE, TokenKindType::T_IS_GREATER_OR_EQUAL,
               TokenKindType::T_SPACESHIP,
      }
   }
};
#endif

void RelationExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == RelationExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Lhs, std::set{SyntaxKind::VariableExpr});
   syntax_assert_child_token(raw, RelationOperator, CHILD_TOKEN_CHOICES.at(Cursor::RelationOperator));
   syntax_assert_child_kind(raw, Rhs, std::set{SyntaxKind::Expr});
#endif
}

ExprSyntax RelationExprSyntax::RelationExprSyntax::getLhs()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Lhs).get()};
}

TokenSyntax RelationExprSyntax::getRelationOperator()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RelationOperator).get()};
}

ExprSyntax RelationExprSyntax::getRhs()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Rhs).get()};
}

RelationExprSyntax RelationExprSyntax::withLhs(std::optional<ExprSyntax> lhs)
{
   RefCountPtr<RawSyntax> lhsRaw;
   if (lhs.has_value()) {
      lhsRaw = lhs->getRaw();
   } else {
      lhsRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<RelationExprSyntax>(lhsRaw, Cursor::Lhs);
}

RelationExprSyntax
RelationExprSyntax::withRelationOperator(std::optional<TokenSyntax> relationOperator)
{
   RefCountPtr<RawSyntax> relationOperatorRaw;
   if (relationOperator.has_value()) {
      relationOperatorRaw = relationOperator->getRaw();
   } else {
      relationOperatorRaw = make_missing_token(T_BOOLEAN_AND);
   }
   return m_data->replaceChild<RelationExprSyntax>(relationOperatorRaw, Cursor::RelationOperator);
}

RelationExprSyntax
RelationExprSyntax::withRhs(std::optional<ExprSyntax> rhs)
{
   RefCountPtr<RawSyntax> rhsRaw;
   if (rhs.has_value()) {
      rhsRaw = rhs->getRaw();
   } else {
      rhsRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<RelationExprSyntax>(rhsRaw, Cursor::Rhs);
}

///
/// CastExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType CastExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      CastExprSyntax::CastOperator, {
         TokenKindType::T_INT_CAST, TokenKindType::T_DOUBLE_CAST,
               TokenKindType::T_STRING_CAST, TokenKindType::T_ARRAY_CAST,
               TokenKindType::T_OBJECT_CAST, TokenKindType::T_BOOL_CAST,
               TokenKindType::T_UNSET_CAST,
      }
   }
};
#endif

void CastExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == CastExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, CastOperator, CHILD_TOKEN_CHOICES.at(Cursor::CastOperator));
   syntax_assert_child_kind(raw, ValueExpr, std::set{SyntaxKind::Expr});
#endif
}

TokenSyntax CastExprSyntax::getCastOperator()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::CastOperator).get()};
}

ExprSyntax CastExprSyntax::getValueExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::ValueExpr).get()};
}

CastExprSyntax CastExprSyntax::withCastOperator(std::optional<TokenSyntax> castOperator)
{
   RefCountPtr<RawSyntax> castOperatorRaw;
   if (castOperator.has_value()) {
      castOperatorRaw = castOperator->getRaw();
   } else {
      castOperatorRaw = make_missing_token(T_INT_CAST);
   }
   return m_data->replaceChild<CastExprSyntax>(castOperatorRaw, Cursor::CastOperator);
}

CastExprSyntax CastExprSyntax::withValueExpr(std::optional<ExprSyntax> valueExpr)
{
   RefCountPtr<RawSyntax> valueExprRaw;
   if (valueExpr.has_value()) {
      valueExprRaw = valueExpr->getRaw();
   } else {
      valueExprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<CastExprSyntax>(valueExprRaw, Cursor::ValueExpr);
}

///
/// ExitExprArgClauseSyntax
///
void ExitExprArgClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ExitExprArgClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, LeftParenToken, std::set{TokenKindType::T_LEFT_PAREN});
   syntax_assert_child_kind(raw, Expr, std::set{SyntaxKind::Expr});
   syntax_assert_child_token(raw, RightParenToken, std::set{TokenKindType::T_LEFT_PAREN});
#endif
}

TokenSyntax ExitExprArgClauseSyntax::getLeftParenToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftParenToken).get()};
}

std::optional<ExprSyntax> ExitExprArgClauseSyntax::getExpr()
{
   RefCountPtr<SyntaxData> exprData = m_data->getChild(Cursor::Expr);
   if (!exprData) {
      return std::nullopt;
   }
   return ExprSyntax {m_root, exprData.get()};
}

TokenSyntax ExitExprArgClauseSyntax::getRightParenToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightParenToken).get()};
}

ExitExprArgClauseSyntax
ExitExprArgClauseSyntax::getLeftParenToken(std::optional<TokenSyntax> leftParentToken)
{
   RefCountPtr<RawSyntax> leftParentTokenRaw;
   if (leftParentToken.has_value()) {
      leftParentTokenRaw = leftParentToken->getRaw();
   } else {
      leftParentTokenRaw = make_missing_token(T_LEFT_PAREN);
   }
   return m_data->replaceChild<ExitExprArgClauseSyntax>(leftParentTokenRaw, Cursor::LeftParenToken);
}

ExitExprArgClauseSyntax
ExitExprArgClauseSyntax::getExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = nullptr;
   }
   return m_data->replaceChild<ExitExprArgClauseSyntax>(exprRaw, Cursor::Expr);
}

ExitExprArgClauseSyntax
ExitExprArgClauseSyntax::getRightParenToken(std::optional<TokenSyntax> rightParentToken)
{
   RefCountPtr<RawSyntax> rightParentTokenRaw;
   if (rightParentToken.has_value()) {
      rightParentTokenRaw = rightParentToken->getRaw();
   } else {
      rightParentTokenRaw = make_missing_token(T_RIGHT_PAREN);
   }
   return m_data->replaceChild<ExitExprArgClauseSyntax>(rightParentTokenRaw, Cursor::RightParenToken);
}

///
/// ExitExprSyntax
///
void ExitExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ExitExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, ExitToken, std::set{TokenKindType::T_EXIT});
   syntax_assert_child_kind(raw, ArgClause, std::set{SyntaxKind::ExitExprArgClause});
#endif
}

TokenSyntax ExitExprSyntax::getExitToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::ExitToken).get()};
}

std::optional<ExitExprArgClauseSyntax> ExitExprSyntax::getArgClause()
{
   RefCountPtr<SyntaxData> argClauseData = m_data->getChild(Cursor::ArgClause);
   if (!argClauseData) {
      return std::nullopt;
   }
   return ExitExprArgClauseSyntax {m_root, argClauseData.get()};
}

ExitExprSyntax ExitExprSyntax::withExitToken(std::optional<TokenSyntax> exitToken)
{
   RefCountPtr<RawSyntax> exitTokenRaw;
   if (exitToken.has_value()) {
      exitTokenRaw = exitToken->getRaw();
   } else {
      exitTokenRaw = make_missing_token(T_EXIT);
   }
   return m_data->replaceChild<ExitExprSyntax>(exitTokenRaw, Cursor::ExitToken);
}

ExitExprSyntax ExitExprSyntax::withArgClause(std::optional<ExitExprArgClauseSyntax> argClause)
{
   RefCountPtr<RawSyntax> argClauseRaw;
   if (argClause.has_value()) {
      argClauseRaw = argClause->getRaw();
   } else {
      argClauseRaw = nullptr;
   }
   return m_data->replaceChild<ExitExprSyntax>(argClauseRaw, Cursor::ArgClause);
}

///
/// YieldExprSyntax
///
void YieldExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == YieldExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, YieldToken, std::set{TokenKindType::T_YIELD});
   syntax_assert_child_token(raw, DoubleArrowToken, std::set{TokenKindType::T_DOUBLE_ARROW});
   syntax_assert_child_kind(raw, KeyExpr, std::set{SyntaxKind::Expr});
   syntax_assert_child_kind(raw, ValueExpr, std::set{SyntaxKind::Expr});
   if (raw->getChild(Cursor::ValueExpr)) {
      assert(raw->getChild(Cursor::KeyExpr) &&
             raw->getChild(Cursor::DoubleArrowToken) &&
             raw->getChild(Cursor::ValueExpr));
   }
#endif
}

TokenSyntax YieldExprSyntax::getYieldToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::YieldToken).get()};
}

std::optional<ExprSyntax> YieldExprSyntax::getKeyExpr()
{
   RefCountPtr<SyntaxData> keyExprData = m_data->getChild(Cursor::KeyExpr);
   if (!keyExprData) {
      return std::nullopt;
   }
   return ExprSyntax {m_root, keyExprData.get()};
}

std::optional<TokenSyntax> YieldExprSyntax::getDoubleArrowToken()
{
   RefCountPtr<SyntaxData> doubleArrowTokenData = m_data->getChild(Cursor::DoubleArrowToken);
   if (!doubleArrowTokenData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, doubleArrowTokenData.get()};
}

std::optional<ExprSyntax> YieldExprSyntax::getValueExpr()
{
   RefCountPtr<SyntaxData> valueExprData = m_data->getChild(Cursor::ValueExpr);
   if (!valueExprData) {
      return std::nullopt;
   }
   return ExprSyntax {m_root, valueExprData.get()};
}

YieldExprSyntax YieldExprSyntax::withYieldToken(std::optional<TokenSyntax> yieldToken)
{
   RefCountPtr<RawSyntax> yieldTokenRaw;
   if (yieldToken.has_value()) {
      yieldTokenRaw = yieldToken->getRaw();
   } else {
      yieldTokenRaw = make_missing_token(T_YIELD);
   }
   return m_data->replaceChild<YieldExprSyntax>(yieldTokenRaw, Cursor::YieldToken);
}

YieldExprSyntax YieldExprSyntax::withKeyExpr(std::optional<ExprSyntax> keyExpr)
{
   RefCountPtr<RawSyntax> keyExprRaw;
   if (keyExpr.has_value()) {
      keyExprRaw = keyExpr->getRaw();
   } else {
      keyExprRaw = nullptr;
   }
   return m_data->replaceChild<YieldExprSyntax>(keyExprRaw, Cursor::KeyExpr);
}

YieldExprSyntax YieldExprSyntax::withDoubleArrowToken(std::optional<TokenSyntax> doubleArrowToken)
{
   RefCountPtr<RawSyntax> doubleArrowTokenRaw;
   if (doubleArrowToken.has_value()) {
      doubleArrowTokenRaw = doubleArrowToken->getRaw();
   } else {
      doubleArrowTokenRaw = nullptr;
   }
   return m_data->replaceChild<YieldExprSyntax>(doubleArrowTokenRaw, Cursor::DoubleArrowToken);
}

YieldExprSyntax YieldExprSyntax::withValueExpr(std::optional<ExprSyntax> valueExpr)
{
   RefCountPtr<RawSyntax> valueExprRaw;
   if (valueExpr.has_value()) {
      valueExprRaw = valueExpr->getRaw();
   } else {
      valueExprRaw = nullptr;
   }
   return m_data->replaceChild<YieldExprSyntax>(valueExprRaw, Cursor::ValueExpr);
}

///
/// YieldFromExprSyntax
///
void YieldFromExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == YieldFromExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, YieldFromToken, std::set{TokenKindType::T_YIELD_FROM});
   syntax_assert_child_kind(raw, Expr, std::set{SyntaxKind::Expr});
#endif
}

TokenSyntax YieldFromExprSyntax::getYieldFromToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::YieldFromToken).get()};
}

ExprSyntax YieldFromExprSyntax::getExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Expr).get()};
}

YieldFromExprSyntax YieldFromExprSyntax::withYieldFromToken(std::optional<TokenSyntax> yieldFromToken)
{
   RefCountPtr<RawSyntax> yieldFromTokenRaw;
   if (yieldFromToken.has_value()) {
      yieldFromTokenRaw = yieldFromToken->getRaw();
   } else {
      yieldFromTokenRaw = make_missing_token(T_YIELD_FROM);
   }
   return m_data->replaceChild<YieldFromExprSyntax>(yieldFromTokenRaw, Cursor::YieldFromToken);
}

YieldFromExprSyntax YieldFromExprSyntax::withExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<YieldFromExprSyntax>(exprRaw, Cursor::Expr);
}

///
/// YieldFromExprSyntax
///
void CloneExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == CloneExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, CloneToken, std::set{TokenKindType::T_CLONE});
   syntax_assert_child_kind(raw, Expr, std::set{SyntaxKind::Expr});
#endif
}

TokenSyntax CloneExprSyntax::getCloneTokenToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::CloneToken).get()};
}

ExprSyntax CloneExprSyntax::getExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::Expr).get()};
}

CloneExprSyntax CloneExprSyntax::withCloneTokenToken(std::optional<TokenSyntax> cloneToken)
{
   RefCountPtr<RawSyntax> cloneTokenRaw;
   if (cloneToken.has_value()) {
      cloneTokenRaw = cloneToken->getRaw();
   } else {
      cloneTokenRaw = make_missing_token(T_CLONE);
   }
   return m_data->replaceChild<CloneExprSyntax>(cloneTokenRaw, Cursor::CloneToken);
}

CloneExprSyntax CloneExprSyntax::withExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<CloneExprSyntax>(exprRaw, Cursor::Expr);
}

///
/// EncapsVariableOffsetSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType EncapsVariableOffsetSyntax::CHILD_TOKEN_CHOICES
{
   {
      EncapsVariableOffsetSyntax::Offset, {
         TokenKindType::T_IDENTIFIER_STRING, TokenKindType::T_NUM_STRING,
               TokenKindType::T_VARIABLE
      }
   }
};
#endif

void EncapsVariableOffsetSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EncapsVariableOffsetSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, MinusSign, std::set{TokenKindType::T_MINUS_SIGN});
   syntax_assert_child_token(raw, Offset, CHILD_TOKEN_CHOICES.at(Cursor::Offset));
#endif
}

std::optional<TokenSyntax> EncapsVariableOffsetSyntax::getMinusSign()
{
   RefCountPtr<SyntaxData> minusSignData = m_data->getChild(Cursor::MinusSign);
   if (!minusSignData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, minusSignData.get()};
}

TokenSyntax EncapsVariableOffsetSyntax::getOffset()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Offset).get()};
}

EncapsVariableOffsetSyntax EncapsVariableOffsetSyntax::withMinusSign(std::optional<TokenSyntax> minusSign)
{
   RefCountPtr<RawSyntax> minusSignRaw;
   if (minusSign.has_value()) {
      minusSignRaw = minusSign->getRaw();
   } else {
      minusSignRaw = nullptr;
   }
   return m_data->replaceChild<EncapsVariableOffsetSyntax>(minusSignRaw, Cursor::MinusSign);
}

EncapsVariableOffsetSyntax EncapsVariableOffsetSyntax::withOffset(std::optional<TokenSyntax> offset)
{
   RefCountPtr<RawSyntax> offsetRaw;
   if (offset.has_value()) {
      offsetRaw = offset->getRaw();
   } else {
      offsetRaw = RawSyntax::missing(TokenKindType::T_IDENTIFIER_STRING,
                                     OwnedString::makeUnowned(get_token_text(TokenKindType::T_IDENTIFIER_STRING)));
   }
   return m_data->replaceChild<EncapsVariableOffsetSyntax>(offsetRaw, Cursor::Offset);
}

///
/// EncapsArrayVarSyntax
///
void EncapsArrayVarSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EncapsArrayVarSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, VarToken, std::set{TokenKindType::T_VARIABLE});
   syntax_assert_child_token(raw, LeftSquareBracket, std::set{TokenKindType::T_LEFT_SQUARE_BRACKET});
   syntax_assert_child_token(raw, RightSquareBracket, std::set{TokenKindType::T_RIGHT_SQUARE_BRACKET});
   syntax_assert_child_kind(raw, Offset, std::set{SyntaxKind::EncapsVariableOffset});
#endif
}

TokenSyntax EncapsArrayVarSyntax::getVarToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::VarToken).get()};
}

TokenSyntax EncapsArrayVarSyntax::getLeftSquareBracket()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftSquareBracket).get()};
}

EncapsVariableOffsetSyntax EncapsArrayVarSyntax::getOffset()
{
   return EncapsVariableOffsetSyntax {m_root, m_data->getChild(Cursor::Offset).get()};
}

TokenSyntax EncapsArrayVarSyntax::getRightSquareBracket()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightSquareBracket).get()};
}

EncapsArrayVarSyntax EncapsArrayVarSyntax::withVarToken(std::optional<TokenSyntax> varToken)
{
   RefCountPtr<RawSyntax> varTokenRaw;
   if (varToken.has_value()) {
      varTokenRaw = varToken->getRaw();
   } else {
      varTokenRaw = RawSyntax::missing(TokenKindType::T_VARIABLE,
                                       OwnedString::makeUnowned(get_token_text(TokenKindType::T_VARIABLE)));
   }
   return m_data->replaceChild<EncapsArrayVarSyntax>(varTokenRaw, Cursor::VarToken);
}

EncapsArrayVarSyntax EncapsArrayVarSyntax::withLeftSquareBracket(std::optional<TokenSyntax> leftSquareBracket)
{
   RefCountPtr<RawSyntax> leftSquareBracketRaw;
   if (leftSquareBracket.has_value()) {
      leftSquareBracketRaw = leftSquareBracket->getRaw();
   } else {
      leftSquareBracketRaw = RawSyntax::missing(TokenKindType::T_LEFT_SQUARE_BRACKET,
                                                OwnedString::makeUnowned(get_token_text(TokenKindType::T_LEFT_SQUARE_BRACKET)));
   }
   return m_data->replaceChild<EncapsArrayVarSyntax>(leftSquareBracketRaw, Cursor::LeftSquareBracket);
}

EncapsArrayVarSyntax EncapsArrayVarSyntax::withOffset(std::optional<EncapsVariableOffsetSyntax> offset)
{
   RefCountPtr<RawSyntax> offsetRaw;
   if (offset.has_value()) {
      offsetRaw = offset->getRaw();
   } else {
      offsetRaw = RawSyntax::missing(SyntaxKind::EncapsVariableOffset);
   }
   return m_data->replaceChild<EncapsArrayVarSyntax>(offsetRaw, Cursor::Offset);
}

EncapsArrayVarSyntax EncapsArrayVarSyntax::withRightSquareBracket(std::optional<TokenSyntax> rightSquareBracket)
{
   RefCountPtr<RawSyntax> rightSquareBracketRaw;
   if (rightSquareBracket.has_value()) {
      rightSquareBracketRaw = rightSquareBracket->getRaw();
   } else {
      rightSquareBracketRaw = RawSyntax::missing(TokenKindType::T_RIGHT_SQUARE_BRACKET,
                                                 OwnedString::makeUnowned(get_token_text(TokenKindType::T_RIGHT_SQUARE_BRACKET)));
   }
   return m_data->replaceChild<EncapsArrayVarSyntax>(rightSquareBracketRaw, Cursor::RightSquareBracket);
}

///
/// EncapsObjPropSyntax
///
void EncapsObjPropSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EncapsObjPropSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, VarToken, std::set{TokenKindType::T_VARIABLE});
   syntax_assert_child_token(raw, ObjOperatorToken, std::set{TokenKindType::T_OBJECT_OPERATOR});
   syntax_assert_child_token(raw, IdentifierToken, std::set{TokenKindType::T_IDENTIFIER_STRING});
#endif
}

TokenSyntax EncapsObjPropSyntax::getVarToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::VarToken).get()};
}

TokenSyntax EncapsObjPropSyntax::getObjOperatorToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::ObjOperatorToken).get()};
}

TokenSyntax EncapsObjPropSyntax::getIdentifierToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::IdentifierToken).get()};
}

EncapsObjPropSyntax EncapsObjPropSyntax::withVarToken(std::optional<TokenSyntax> varToken)
{
   RefCountPtr<RawSyntax> varTokenRaw;
   if (varToken.has_value()) {
      varTokenRaw = varToken->getRaw();
   } else {
      varTokenRaw = RawSyntax::missing(TokenKindType::T_VARIABLE,
                                       OwnedString::makeUnowned(get_token_text(TokenKindType::T_VARIABLE)));
   }
   return m_data->replaceChild<EncapsObjPropSyntax>(varTokenRaw, Cursor::VarToken);
}

EncapsObjPropSyntax EncapsObjPropSyntax::withObjOperatorToken(std::optional<TokenSyntax> objOperatorToken)
{
   RefCountPtr<RawSyntax> objOperatorTokenRaw;
   if (objOperatorToken.has_value()) {
      objOperatorTokenRaw = objOperatorToken->getRaw();
   } else {
      objOperatorTokenRaw = RawSyntax::missing(TokenKindType::T_OBJECT_OPERATOR,
                                               OwnedString::makeUnowned(get_token_text(TokenKindType::T_OBJECT_OPERATOR)));
   }
   return m_data->replaceChild<EncapsObjPropSyntax>(objOperatorTokenRaw, Cursor::ObjOperatorToken);
}

EncapsObjPropSyntax EncapsObjPropSyntax::withIdentifierToken(std::optional<TokenSyntax> identifierToken)
{
   RefCountPtr<RawSyntax> identifierTokenRaw;
   if (identifierToken.has_value()) {
      identifierTokenRaw = identifierToken->getRaw();
   } else {
      identifierTokenRaw = RawSyntax::missing(TokenKindType::T_IDENTIFIER_STRING,
                                              OwnedString::makeUnowned(get_token_text(TokenKindType::T_IDENTIFIER_STRING)));
   }
   return m_data->replaceChild<EncapsObjPropSyntax>(identifierTokenRaw, Cursor::IdentifierToken);
}

///
/// EncapsDollarCurlyExprSyntax
///
void EncapsDollarCurlyExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EncapsDollarCurlyExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, DollarOpenCurlyToken, std::set{TokenKindType::T_DOLLAR_OPEN_CURLY_BRACES});
   syntax_assert_child_token(raw, CloseCurlyToken, std::set{TokenKindType::T_RIGHT_BRACE});
   syntax_assert_child_kind(raw, Expr, std::set{SyntaxKind::Expr});
#endif
}

TokenSyntax EncapsDollarCurlyExprSyntax::getDollarOpenCurlyToken()
{
   return TokenSyntax {m_root, m_data->getChild(DollarOpenCurlyToken).get()};
}

ExprSyntax EncapsDollarCurlyExprSyntax::getExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Expr).get()};
}

TokenSyntax EncapsDollarCurlyExprSyntax::getCloseCurlyToken()
{
   return TokenSyntax {m_root, m_data->getChild(CloseCurlyToken).get()};
}

EncapsDollarCurlyExprSyntax
EncapsDollarCurlyExprSyntax::withDollarOpenCurlyToken(std::optional<TokenSyntax> dollarOpenCurlyToken)
{
   RefCountPtr<RawSyntax> dollarOpenCurlyTokenRaw;
   if (dollarOpenCurlyToken.has_value()) {
      dollarOpenCurlyTokenRaw = dollarOpenCurlyToken->getRaw();
   } else {
      dollarOpenCurlyTokenRaw = make_missing_token(T_DOLLAR_OPEN_CURLY_BRACES);
   }
   return m_data->replaceChild<EncapsDollarCurlyExprSyntax>(dollarOpenCurlyTokenRaw, Cursor::DollarOpenCurlyToken);
}

EncapsDollarCurlyExprSyntax EncapsDollarCurlyExprSyntax::withExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> exprRaw;
   if (expr.has_value()) {
      exprRaw = expr->getRaw();
   } else {
      exprRaw = RawSyntax::missing(SyntaxKind::UnknownExpr);
   }
   return m_data->replaceChild<EncapsDollarCurlyExprSyntax>(exprRaw, Cursor::Expr);
}

EncapsDollarCurlyExprSyntax EncapsDollarCurlyExprSyntax::withCloseCurlyToken(std::optional<TokenSyntax> closeCurlyToken)
{
   RefCountPtr<RawSyntax> closeCurlyTokenRaw;
   if (closeCurlyToken.has_value()) {
      closeCurlyTokenRaw = closeCurlyToken->getRaw();
   } else {
      closeCurlyTokenRaw = make_missing_token(T_RIGHT_BRACE);
   }
   return m_data->replaceChild<EncapsDollarCurlyExprSyntax>(closeCurlyTokenRaw, Cursor::CloseCurlyToken);
}

///
/// EncapsDollarCurlyExprSyntax
///
void EncapsDollarCurlyVarSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EncapsDollarCurlyVarSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, DollarOpenCurlyToken, std::set{TokenKindType::T_DOLLAR_OPEN_CURLY_BRACES});
   syntax_assert_child_token(raw, Varname, std::set{TokenKindType::T_IDENTIFIER_STRING});
   syntax_assert_child_token(raw, CloseCurlyToken, std::set{TokenKindType::T_RIGHT_BRACE});
#endif
}

TokenSyntax EncapsDollarCurlyVarSyntax::getDollarOpenCurlyToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::DollarOpenCurlyToken).get()};
}

TokenSyntax EncapsDollarCurlyVarSyntax::getVarname()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Varname).get()};
}

TokenSyntax EncapsDollarCurlyVarSyntax::getCloseCurlyToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::CloseCurlyToken).get()};
}

EncapsDollarCurlyVarSyntax
EncapsDollarCurlyVarSyntax::withDollarOpenCurlyToken(std::optional<TokenSyntax> dollarOpenCurlyToken)
{
   RefCountPtr<RawSyntax> dollarOpenCurlyTokenRaw;
   if (dollarOpenCurlyToken.has_value()) {
      dollarOpenCurlyTokenRaw = dollarOpenCurlyToken->getRaw();
   } else {
      dollarOpenCurlyTokenRaw = make_missing_token(T_DOLLAR_OPEN_CURLY_BRACES);
   }
   return m_data->replaceChild<EncapsDollarCurlyVarSyntax>(dollarOpenCurlyTokenRaw, DollarOpenCurlyToken);
}

EncapsDollarCurlyVarSyntax
EncapsDollarCurlyVarSyntax::withVarname(std::optional<ExprSyntax> varname)
{
   RefCountPtr<RawSyntax> varnameRaw;
   if (varname.has_value()) {
      varnameRaw = varname->getRaw();
   } else {
      varnameRaw = make_missing_token(T_IDENTIFIER_STRING);
   }
   return m_data->replaceChild<EncapsDollarCurlyVarSyntax>(varnameRaw, Varname);
}

EncapsDollarCurlyVarSyntax
EncapsDollarCurlyVarSyntax::withCloseCurlyToken(std::optional<TokenSyntax> closeCurlyToken)
{
   RefCountPtr<RawSyntax> closeCurlyTokenRaw;
   if (closeCurlyToken.has_value()) {
      closeCurlyTokenRaw = closeCurlyToken->getRaw();
   } else {
      closeCurlyTokenRaw = make_missing_token(T_RIGHT_BRACE);
   }
   return m_data->replaceChild<EncapsDollarCurlyVarSyntax>(closeCurlyTokenRaw, CloseCurlyToken);
}

///
/// EncapsDollarCurlyArraySyntax
///
void EncapsDollarCurlyArraySyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EncapsDollarCurlyArraySyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, DollarOpenCurlyToken, std::set{TokenKindType::T_DOLLAR_OPEN_CURLY_BRACES});
   syntax_assert_child_token(raw, Varname, std::set{TokenKindType::T_IDENTIFIER_STRING});
   syntax_assert_child_token(raw, LeftSquareBracketToken, std::set{TokenKindType::T_LEFT_SQUARE_BRACKET});
   syntax_assert_child_token(raw, RightSquareBracketToken, std::set{TokenKindType::T_RIGHT_SQUARE_BRACKET});
   syntax_assert_child_token(raw, CloseCurlyToken, std::set{TokenKindType::T_RIGHT_BRACE});
#endif
}

TokenSyntax EncapsDollarCurlyArraySyntax::getDollarOpenCurlyToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::DollarOpenCurlyToken).get()};
}

TokenSyntax EncapsDollarCurlyArraySyntax::getVarname()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Varname).get()};
}

TokenSyntax EncapsDollarCurlyArraySyntax::getLeftSquareBracketToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftSquareBracketToken).get()};
}

ExprSyntax EncapsDollarCurlyArraySyntax::getIndexExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::IndexExpr).get()};
}

TokenSyntax EncapsDollarCurlyArraySyntax::getRightSquareBracketToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightSquareBracketToken).get()};
}

TokenSyntax EncapsDollarCurlyArraySyntax::getCloseCurlyToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::CloseCurlyToken).get()};
}

EncapsDollarCurlyArraySyntax
EncapsDollarCurlyArraySyntax::withDollarOpenCurlyToken(std::optional<TokenSyntax> dollarOpenCurlyToken)
{
   RefCountPtr<RawSyntax> dollarOpenCurlyTokenRaw;
   if (dollarOpenCurlyToken.has_value()) {
      dollarOpenCurlyTokenRaw = dollarOpenCurlyToken->getRaw();
   } else {
      dollarOpenCurlyTokenRaw = make_missing_token(T_DOLLAR_OPEN_CURLY_BRACES);
   }
   return m_data->replaceChild<EncapsDollarCurlyArraySyntax>(dollarOpenCurlyTokenRaw, DollarOpenCurlyToken);
}

EncapsDollarCurlyArraySyntax
EncapsDollarCurlyArraySyntax::withVarname(std::optional<TokenSyntax> varname)
{
   RefCountPtr<RawSyntax> varnameRaw;
   if (varname.has_value()) {
      varnameRaw = varname->getRaw();
   } else {
      varnameRaw = make_missing_token(T_IDENTIFIER_STRING);
   }
   return m_data->replaceChild<EncapsDollarCurlyArraySyntax>(varnameRaw, Varname);
}

EncapsDollarCurlyArraySyntax
EncapsDollarCurlyArraySyntax::withLeftSquareBracketToken(std::optional<TokenSyntax> leftSquareBracketToken)
{
   RefCountPtr<RawSyntax> leftSquareBracketTokenRaw;
   if (leftSquareBracketToken.has_value()) {
      leftSquareBracketTokenRaw = leftSquareBracketToken->getRaw();
   } else {
      leftSquareBracketTokenRaw = make_missing_token(T_LEFT_SQUARE_BRACKET);
   }
   return m_data->replaceChild<EncapsDollarCurlyArraySyntax>(leftSquareBracketTokenRaw, LeftSquareBracketToken);
}

EncapsDollarCurlyArraySyntax
EncapsDollarCurlyArraySyntax::withIndexExpr(std::optional<ExprSyntax> indexExpr)
{
   RefCountPtr<RawSyntax> indexExprRaw;
   if (indexExpr.has_value()) {
      indexExprRaw = indexExpr->getRaw();
   } else {
      indexExprRaw = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<EncapsDollarCurlyArraySyntax>(indexExprRaw, IndexExpr);
}

EncapsDollarCurlyArraySyntax
EncapsDollarCurlyArraySyntax::withRightSquareBracketToken(std::optional<TokenSyntax> rightSquareBracketToken)
{
   RefCountPtr<RawSyntax> rightSquareBracketTokenRaw;
   if (rightSquareBracketToken.has_value()) {
      rightSquareBracketTokenRaw = rightSquareBracketToken->getRaw();
   } else {
      rightSquareBracketTokenRaw = make_missing_token(T_RIGHT_SQUARE_BRACKET);
   }
   return m_data->replaceChild<EncapsDollarCurlyArraySyntax>(rightSquareBracketTokenRaw, RightSquareBracketToken);
}

EncapsDollarCurlyArraySyntax
EncapsDollarCurlyArraySyntax::withCloseCurlyToken(std::optional<TokenSyntax> closeCurlyToken)
{
   RefCountPtr<RawSyntax> closeCurlyTokenRaw;
   if (closeCurlyToken.has_value()) {
      closeCurlyTokenRaw = closeCurlyToken->getRaw();
   } else {
      closeCurlyTokenRaw = make_missing_token(T_RIGHT_BRACE);
   }
   return m_data->replaceChild<EncapsDollarCurlyArraySyntax>(closeCurlyTokenRaw, CloseCurlyToken);
}

///
/// EncapsCurlyVariableSyntax
///
void EncapsCurlyVariableSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EncapsCurlyVariableSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, CurlyOpen, std::set{TokenKindType::T_CURLY_OPEN});
   syntax_assert_child_kind(raw, Variable, std::set{SyntaxKind::VariableExpr});
   syntax_assert_child_token(raw, CloseCurlyToken, std::set{TokenKindType::T_RIGHT_BRACE});
#endif
}

TokenSyntax EncapsCurlyVariableSyntax::getCurlyOpen()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::CurlyOpen).get()};
}

VariableExprSyntax EncapsCurlyVariableSyntax::getVariable()
{
   return VariableExprSyntax {m_root, m_data->getChild(Cursor::Variable).get()};
}

TokenSyntax EncapsCurlyVariableSyntax::getCloseCurlyToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::CloseCurlyToken).get()};
}

EncapsCurlyVariableSyntax
EncapsCurlyVariableSyntax::withCurlyOpen(std::optional<TokenSyntax> curlyOpen)
{
   RefCountPtr<RawSyntax> curlyOpenRaw;
   if (curlyOpen.has_value()) {
      curlyOpenRaw = curlyOpen->getRaw();
   } else {
      curlyOpenRaw = make_missing_token(T_CURLY_OPEN);
   }
   return m_data->replaceChild<EncapsCurlyVariableSyntax>(curlyOpenRaw, CurlyOpen);
}

EncapsCurlyVariableSyntax
EncapsCurlyVariableSyntax::withVariable(std::optional<VariableExprSyntax> variable)
{
   RefCountPtr<RawSyntax> variableRaw;
   if (variable.has_value()) {
      variableRaw = variable->getRaw();
   } else {
      variableRaw = RawSyntax::missing(SyntaxKind::VariableExpr);
   }
   return m_data->replaceChild<EncapsCurlyVariableSyntax>(variableRaw, Variable);
}

EncapsCurlyVariableSyntax
EncapsCurlyVariableSyntax::withCloseCurlyToken(std::optional<TokenSyntax> closeCurlyToken)
{
   RefCountPtr<RawSyntax> closeCurlyTokenRaw;
   if (closeCurlyToken.has_value()) {
      closeCurlyTokenRaw = closeCurlyToken->getRaw();
   } else {
      closeCurlyTokenRaw = make_missing_token(T_RIGHT_BRACE);
   }
   return m_data->replaceChild<EncapsCurlyVariableSyntax>(closeCurlyTokenRaw, CloseCurlyToken);
}

///
/// EncapsVariableSyntax
///

#ifdef POLAR_DEBUG_BUILD
const NodeChoicesType EncapsVariableSyntax::CHILD_NODE_CHOICES
{
   {
      EncapsVariableSyntax::Var, {
         SyntaxKind::EncapsArrayVar, SyntaxKind::EncapsObjProp,
               SyntaxKind::EncapsDollarCurlyExpr, SyntaxKind::EncapsDollarCurlyVar,
               SyntaxKind::EncapsDollarCurlyArray, SyntaxKind::EncapsCurlyVariable

      }
   }
};
#endif

void EncapsVariableSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EncapsVariableSyntax::CHILDREN_COUNT);
   if (const RefCountPtr<RawSyntax> &varChild = raw->getChild(Cursor::Var)) {
      if (varChild->isToken()) {
         syntax_assert_child_token(raw, Var, std::set{TokenKindType::T_IDENTIFIER_STRING});
      } else {
         syntax_assert_child_kind(raw, Var, CHILD_NODE_CHOICES.at(Cursor::Var));
      }
   }
#endif
}

Syntax EncapsVariableSyntax::getVariable()
{
   return Syntax {m_root, m_data->getChild(Cursor::Var).get()};
}

EncapsVariableSyntax EncapsVariableSyntax::withVariable(std::optional<Syntax> var)
{
   RefCountPtr<RawSyntax> varRaw;
   if (var.has_value()) {
      varRaw = var->getRaw();
   } else {
      varRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<EncapsVariableSyntax>(varRaw, Cursor::Var);
}

///
/// EncapsListItemSyntax
///
void EncapsListItemSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EncapsListItemSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, EncapsVariable, std::set{SyntaxKind::EncapsVariable});
   syntax_assert_child_token(raw, StrLiteral, std::set{TokenKindType::T_ENCAPSED_AND_WHITESPACE});
   assert(raw->getChild(Cursor::EncapsVariable) || raw->getChild(Cursor::StrLiteral));
#endif
}

std::optional<TokenSyntax> EncapsListItemSyntax::getStrLiteral()
{
   RefCountPtr<SyntaxData> strLiteralData = m_data->getChild(Cursor::StrLiteral);
   if (!strLiteralData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, strLiteralData.get()};
}

std::optional<EncapsVariableSyntax> EncapsListItemSyntax::getEncapsVariable()
{
   RefCountPtr<SyntaxData> encapsVarData = m_data->getChild(Cursor::EncapsVariable);
   if (!encapsVarData) {
      return std::nullopt;
   }
   return EncapsVariableSyntax {m_root, encapsVarData.get()};
}

EncapsListItemSyntax EncapsListItemSyntax::withEncapsListItemSyntax(std::optional<TokenSyntax> strLiteral)
{
   RefCountPtr<RawSyntax> strLiteralRaw;
   if (strLiteral.has_value()) {
      strLiteralRaw = strLiteral->getRaw();
   } else {
      strLiteralRaw = make_missing_token(T_ENCAPSED_AND_WHITESPACE);
   }
   return m_data->replaceChild<EncapsListItemSyntax>(strLiteralRaw, Cursor::StrLiteral);
}

EncapsListItemSyntax EncapsListItemSyntax::withEncapsVariable(std::optional<EncapsVariableSyntax> encapsVar)
{
   RefCountPtr<RawSyntax> encapsVarRaw;
   if (encapsVar.has_value()) {
      encapsVarRaw = encapsVar->getRaw();
   } else {
      encapsVarRaw = RawSyntax::missing(SyntaxKind::EncapsVariable);
   }
   return m_data->replaceChild<EncapsListItemSyntax>(encapsVarRaw, Cursor::EncapsVariable);
}

///
/// BackticksClauseSyntax
///

void BackticksClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == BackticksClauseSyntax::CHILDREN_COUNT);
   if (const RefCountPtr<RawSyntax> &backticksChild = raw->getChild(Cursor::Backticks)) {
      if (backticksChild->isToken()) {
         syntax_assert_child_token(raw, Backticks, std::set{TokenKindType::T_ENCAPSED_AND_WHITESPACE});
      } else {
         syntax_assert_child_kind(raw, Backticks, std::set{SyntaxKind::EncapsList});
      }
   }
#endif
}

Syntax BackticksClauseSyntax::getBackticks()
{
   return Syntax {m_root, m_data->getChild(Cursor::Backticks).get()};
}

BackticksClauseSyntax BackticksClauseSyntax::withBackticks(std::optional<Syntax> backticks)
{
   RefCountPtr<RawSyntax> backticksRaw;
   if (backticks.has_value()) {
      backticksRaw = backticks->getRaw();
   } else {
      backticksRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<BackticksClauseSyntax>(backticksRaw, Cursor::Backticks);
}

///
/// HeredocExprSyntax
///
void HeredocExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == HeredocExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, StartHeredocToken, std::set{TokenKindType::T_START_HEREDOC});
   syntax_assert_child_token(raw, EndHeredocToken, std::set{TokenKindType::T_END_HEREDOC});
   if (const RefCountPtr<RawSyntax> &textClauseChild = raw->getChild(Cursor::TextClause)) {
      if (textClauseChild->isToken()) {
         syntax_assert_child_token(raw, TextClause, std::set{TokenKindType::T_ENCAPSED_AND_WHITESPACE});
      } else {
         syntax_assert_child_kind(raw, TextClause, std::set{SyntaxKind::EncapsList});
      }
   }
#endif
}

TokenSyntax HeredocExprSyntax::getStartHeredocToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::StartHeredocToken).get()};
}

std::optional<Syntax> HeredocExprSyntax::getTextClause()
{
   RefCountPtr<SyntaxData> textClauseData = m_data->getChild(Cursor::TextClause);
   if (!textClauseData) {
      return std::nullopt;
   }
   return Syntax {m_root, textClauseData.get()};
}

TokenSyntax HeredocExprSyntax::getEndHeredocToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::EndHeredocToken).get()};
}

HeredocExprSyntax HeredocExprSyntax::withStartHeredocToken(std::optional<TokenSyntax> startHeredocToken)
{
   RefCountPtr<RawSyntax> startHeredocTokenRaw;
   if (startHeredocToken.has_value()) {
      startHeredocTokenRaw = startHeredocToken->getRaw();
   } else {
      startHeredocTokenRaw = make_missing_token(T_START_HEREDOC);
   }
   return m_data->replaceChild<HeredocExprSyntax>(startHeredocTokenRaw, Cursor::StartHeredocToken);
}

HeredocExprSyntax HeredocExprSyntax::withTextClause(std::optional<Syntax> textClause)
{
   RefCountPtr<RawSyntax> textClauseRaw;
   if (textClause.has_value()) {
      textClauseRaw = textClause->getRaw();
   } else {
      textClauseRaw = nullptr;
   }
   return m_data->replaceChild<HeredocExprSyntax>(textClauseRaw, Cursor::TextClause);
}

HeredocExprSyntax HeredocExprSyntax::withEndHeredocToken(std::optional<TokenSyntax> endHeredocToken)
{
   RefCountPtr<RawSyntax> endHeredocTokenRaw;
   if (endHeredocToken.has_value()) {
      endHeredocTokenRaw = endHeredocToken->getRaw();
   } else {
      endHeredocTokenRaw = make_missing_token(T_END_HEREDOC);
   }
   return m_data->replaceChild<HeredocExprSyntax>(endHeredocTokenRaw, Cursor::EndHeredocToken);
}

///
/// EncapsListStringExprSyntax
///
void EncapsListStringExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == EncapsListStringExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, LeftQuoteToken, std::set{TokenKindType::T_DOUBLE_QUOTE});
   syntax_assert_child_token(raw, RightQuoteToken, std::set{TokenKindType::T_DOUBLE_QUOTE});
   syntax_assert_child_kind(raw, EncapsList, std::set{SyntaxKind::EncapsList});
#endif
}

TokenSyntax EncapsListStringExprSyntax::getLeftQuoteToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftQuoteToken).get()};
}

EncapsItemListSyntax EncapsListStringExprSyntax::getEncapsList()
{
   return EncapsItemListSyntax {m_root, m_data->getChild(Cursor::EncapsList).get()};
}

TokenSyntax EncapsListStringExprSyntax::getRightQuoteToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightQuoteToken).get()};
}

EncapsListStringExprSyntax
EncapsListStringExprSyntax::withLeftQuoteToken(std::optional<TokenSyntax> leftQuoteToken)
{
   RefCountPtr<RawSyntax> leftQuoteTokenRaw;
   if (leftQuoteToken.has_value()) {
      leftQuoteTokenRaw = leftQuoteToken->getRaw();
   } else {
      leftQuoteTokenRaw = make_missing_token(T_DOUBLE_QUOTE);
   }
   return m_data->replaceChild<EncapsListStringExprSyntax>(leftQuoteTokenRaw, Cursor::LeftQuoteToken);
}

EncapsListStringExprSyntax
EncapsListStringExprSyntax::withEncapsList(std::optional<EncapsItemListSyntax> encapsList)
{
   RefCountPtr<RawSyntax> encapsListRaw;
   if (encapsList.has_value()) {
      encapsListRaw = encapsList->getRaw();
   } else {
      encapsListRaw = RawSyntax::missing(SyntaxKind::EncapsList);
   }
   return m_data->replaceChild<EncapsListStringExprSyntax>(encapsListRaw, Cursor::EncapsList);
}

EncapsListStringExprSyntax
EncapsListStringExprSyntax::withRightQuoteToken(std::optional<TokenSyntax> rightQuoteToken)
{
   RefCountPtr<RawSyntax> rightQuoteTokenRaw;
   if (rightQuoteToken.has_value()) {
      rightQuoteTokenRaw = rightQuoteToken->getRaw();
   } else {
      rightQuoteTokenRaw = make_missing_token(T_DOUBLE_QUOTE);
   }
   return m_data->replaceChild<EncapsListStringExprSyntax>(rightQuoteTokenRaw, Cursor::RightQuoteToken);
}

///
/// TernaryExprSyntax
///
void TernaryExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == TernaryExprSyntax::CHILDREN_COUNT);

   syntax_assert_child_kind(raw, ConditionExpr, std::set{SyntaxKind::Expr});
   syntax_assert_child_kind(raw, FirstChoice, std::set{SyntaxKind::Expr});
   syntax_assert_child_kind(raw, SecondChoice, std::set{SyntaxKind::Expr});
   syntax_assert_child_token(raw, QuestionMark, std::set{TokenKindType::T_QUESTION_MARK});
   syntax_assert_child_token(raw, ColonMark, std::set{TokenKindType::T_COLON});
#endif
}

ExprSyntax TernaryExprSyntax::getConditionExpr()
{
   return ExprSyntax{m_root, m_data->getChild(Cursor::ConditionExpr).get()};
}

TokenSyntax TernaryExprSyntax::getQuestionMark()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::QuestionMark).get()};
}

std::optional<ExprSyntax> TernaryExprSyntax::getFirstChoice()
{
   RefCountPtr<SyntaxData> firstChoiceData = m_data->getChild(Cursor::FirstChoice);
   if (!firstChoiceData) {
      return std::nullopt;
   }
   return ExprSyntax{m_root, firstChoiceData.get()};
}

TokenSyntax TernaryExprSyntax::getColonMark()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::ColonMark).get()};
}

ExprSyntax TernaryExprSyntax::getSecondChoice()
{
   return ExprSyntax{m_root, m_data->getChild(Cursor::SecondChoice).get()};
}

TernaryExprSyntax TernaryExprSyntax::withConditionExpr(std::optional<ExprSyntax> conditionExpr)
{
   RefCountPtr<RawSyntax> rawConditionExpr;
   if (conditionExpr.has_value()) {
      rawConditionExpr = conditionExpr->getRaw();
   } else {
      rawConditionExpr = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<TernaryExprSyntax>(rawConditionExpr, Cursor::ConditionExpr);
}

TernaryExprSyntax TernaryExprSyntax::withQuestionMark(std::optional<TokenSyntax> questionMark)
{
   RefCountPtr<RawSyntax> rawQuestionMark;
   if (questionMark.has_value()) {
      rawQuestionMark = questionMark->getRaw();
   } else {
      rawQuestionMark = RawSyntax::missing(TokenKindType::T_QUESTION_MARK,
                                           OwnedString::makeUnowned(get_token_text(TokenKindType::T_QUESTION_MARK)));
   }
   return m_data->replaceChild<TernaryExprSyntax>(rawQuestionMark, Cursor::QuestionMark);
}

TernaryExprSyntax TernaryExprSyntax::withFirstChoice(std::optional<ExprSyntax> firstChoice)
{
   RefCountPtr<RawSyntax> rawFirstChoice;
   if (firstChoice.has_value()) {
      rawFirstChoice = firstChoice->getRaw();
   } else {
      rawFirstChoice = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<TernaryExprSyntax>(rawFirstChoice, Cursor::FirstChoice);
}

TernaryExprSyntax TernaryExprSyntax::withColonMark(std::optional<TokenSyntax> colonMark)
{
   RefCountPtr<RawSyntax> rawColonMark;
   if (colonMark.has_value()) {
      rawColonMark = colonMark->getRaw();
   } else {
      rawColonMark = RawSyntax::missing(TokenKindType::T_COLON,
                                        OwnedString::makeUnowned(get_token_text(TokenKindType::T_COLON)));
   }
   return m_data->replaceChild<TernaryExprSyntax>(rawColonMark, Cursor::ColonMark);
}

TernaryExprSyntax TernaryExprSyntax::withSecondChoice(std::optional<ExprSyntax> secondChoice)
{
   RefCountPtr<RawSyntax> rawSecondChoice;
   if (secondChoice.has_value()) {
      rawSecondChoice = secondChoice->getRaw();
   } else {
      rawSecondChoice = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<TernaryExprSyntax>(rawSecondChoice, Cursor::SecondChoice);
}

void SequenceExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == SequenceExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Elements, std::set{SyntaxKind::ExprList});
#endif
}

ExprListSyntax SequenceExprSyntax::getElements()
{
   return ExprListSyntax{m_root, m_data->getChild(Cursor::Elements).get()};
}

SequenceExprSyntax SequenceExprSyntax::withElements(std::optional<ExprListSyntax> elements)
{
   RefCountPtr<RawSyntax> rawElements;
   if (elements.has_value()) {
      rawElements = elements->getRaw();
   } else {
      rawElements = RawSyntax::missing(SyntaxKind::ExprList);
   }
   return m_data->replaceChild<SequenceExprSyntax>(rawElements, Cursor::Elements);
}

SequenceExprSyntax SequenceExprSyntax::addElement(ExprSyntax expr)
{
   RefCountPtr<RawSyntax> elements = getRaw()->getChild(Cursor::Elements);
   if (elements) {
      elements = elements->append(expr.getRaw());
   } else {
      elements = RawSyntax::make(SyntaxKind::ExprList, {expr.getRaw()}, SourcePresence::Present);
   }
   return m_data->replaceChild<SequenceExprSyntax>(elements, Cursor::Elements);
}

///
/// PrefixOperatorExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType PrefixOperatorExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      PrefixOperatorExprSyntax::OperatorToken, {
         TokenKindType::T_PLUS_SIGN, TokenKindType::T_MINUS_SIGN,
               TokenKindType::T_EXCLAMATION_MARK, TokenKindType::T_TILDE,
               TokenKindType::T_ERROR_SUPPRESS_SIGN, TokenKindType::T_INC,
               TokenKindType::T_DEC
      }
   }
};
#endif

void PrefixOperatorExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == PrefixOperatorExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, OperatorToken, CHILD_TOKEN_CHOICES.at(Cursor::OperatorToken));
   const RefCountPtr<RawSyntax> &operatorToken = raw->getChild(Cursor::OperatorToken);
   TokenKindType operatorKind = operatorToken->getTokenKind();
   if (operatorKind == TokenKindType::T_INC || operatorKind == TokenKindType::T_DEC) {
      assert(raw->getChild(Cursor::Expr)->kindOf(SyntaxKind::VariableExpr));
   } else {
      syntax_assert_child_kind(raw, Expr, std::set{SyntaxKind::Expr});
   }
#endif
}

std::optional<TokenSyntax> PrefixOperatorExprSyntax::getOperatorToken()
{
   RefCountPtr<SyntaxData> operatorTokenData = m_data->getChild(Cursor::OperatorToken);
   if (!operatorTokenData) {
      return std::nullopt;
   }
   return TokenSyntax{m_root, operatorTokenData.get()};
}

ExprSyntax PrefixOperatorExprSyntax::getExpr()
{
   return ExprSyntax{m_root, m_data->getChild(Cursor::Expr).get()};
}

PrefixOperatorExprSyntax PrefixOperatorExprSyntax::withOperatorToken(std::optional<TokenSyntax> operatorToken)
{
   RefCountPtr<RawSyntax> rawOperatorToken;
   if (operatorToken.has_value()) {
      rawOperatorToken = operatorToken->getRaw();
   } else {
      rawOperatorToken = nullptr;
   }
   return m_data->replaceChild<PrefixOperatorExprSyntax>(rawOperatorToken, Cursor::OperatorToken);
}

PrefixOperatorExprSyntax PrefixOperatorExprSyntax::withExpr(std::optional<TokenSyntax> expr)
{
   RefCountPtr<RawSyntax> rawExpr;
   if (expr.has_value()) {
      rawExpr = expr->getRaw();
   } else {
      rawExpr = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<PrefixOperatorExprSyntax>(rawExpr, Cursor::Expr);
}

///
/// PostfixOperatorExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType PostfixOperatorExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      PrefixOperatorExprSyntax::OperatorToken, {
         TokenKindType::T_INC, TokenKindType::T_DEC
      }
   }
};
#endif

void PostfixOperatorExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == PostfixOperatorExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, OperatorToken, CHILD_TOKEN_CHOICES.at(Cursor::OperatorToken));
   const RefCountPtr<RawSyntax> &operatorToken = raw->getChild(Cursor::OperatorToken);
   TokenKindType operatorKind = operatorToken->getTokenKind();
   if (operatorKind == TokenKindType::T_INC || operatorKind == TokenKindType::T_DEC) {
      assert(raw->getChild(Cursor::Expr)->kindOf(SyntaxKind::VariableExpr));
   } else {
      syntax_assert_child_kind(raw, Expr, std::set{SyntaxKind::Expr});
   }
#endif
}

ExprSyntax PostfixOperatorExprSyntax::getExpr()
{
   return ExprSyntax{m_root, m_data->getChild(Cursor::Expr).get()};
}

TokenSyntax PostfixOperatorExprSyntax::getOperatorToken()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::OperatorToken).get()};
}

PostfixOperatorExprSyntax PostfixOperatorExprSyntax::withExpr(std::optional<ExprSyntax> expr)
{
   RefCountPtr<RawSyntax> rawExpr;
   if (expr.has_value()) {
      rawExpr = expr->getRaw();
   } else {
      rawExpr = RawSyntax::missing(SyntaxKind::Expr);
   }
   return m_data->replaceChild<PostfixOperatorExprSyntax>(rawExpr, Cursor::Expr);
}

PostfixOperatorExprSyntax PostfixOperatorExprSyntax::withOperatorToken(std::optional<TokenSyntax> operatorToken)
{
   RefCountPtr<RawSyntax> rawOperatorToken;
   if (operatorToken.has_value()) {
      rawOperatorToken = operatorToken->getRaw();
   } else {
      rawOperatorToken = make_missing_token(T_INC);
   }
   return m_data->replaceChild<PostfixOperatorExprSyntax>(rawOperatorToken, Cursor::OperatorToken);
}

///
/// BinaryOperatorExprSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType BinaryOperatorExprSyntax::CHILD_TOKEN_CHOICES
{
   {
      BinaryOperatorExprSyntax::OperatorToken, {
         TokenKindType::T_STR_CONCAT, TokenKindType::T_PLUS_SIGN,
               TokenKindType::T_MINUS_SIGN, TokenKindType::T_MUL_SIGN,
               TokenKindType::T_DIV_SIGN, TokenKindType::T_POW,
               TokenKindType::T_MOD_SIGN, TokenKindType::T_SL,
               TokenKindType::T_SR, TokenKindType::T_COALESCE
      }
   }
};
#endif

void BinaryOperatorExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == BinaryOperatorExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, Lhs, std::set{SyntaxKind::Expr});
   syntax_assert_child_kind(raw, Rhs, std::set{SyntaxKind::Expr});
   syntax_assert_child_token(raw, OperatorToken, CHILD_TOKEN_CHOICES.at(Cursor::OperatorToken));
#endif
}

TokenSyntax BinaryOperatorExprSyntax::getOperatorToken()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::OperatorToken).get()};
}

BinaryOperatorExprSyntax BinaryOperatorExprSyntax::withOperatorToken(std::optional<TokenSyntax> operatorToken)
{
   RefCountPtr<RawSyntax> rawOperatorToken;
   if (operatorToken.has_value()) {
      rawOperatorToken = operatorToken->getRaw();
   } else {
      rawOperatorToken = make_missing_token(T_PLUS_SIGN);
   }
   return m_data->replaceChild<BinaryOperatorExprSyntax>(rawOperatorToken, Cursor::OperatorToken);
}

///
/// InstanceofExprSyntax
///
void InstanceofExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == InstanceofExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_kind(raw, InstanceExpr, std::set{SyntaxKind::Expr});
   syntax_assert_child_token(raw, InstanceofToken, std::set{TokenKindType::T_INSTANCEOF});
   syntax_assert_child_kind(raw, ClassNameRef, std::set{SyntaxKind::ClassNameRefClause});
#endif
}

ExprSyntax InstanceofExprSyntax::getInstanceExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::InstanceExpr).get()};
}

TokenSyntax InstanceofExprSyntax::getInstanceofToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::InstanceofToken).get()};
}

ClassNameRefClauseSyntax InstanceofExprSyntax::getClassNameRef()
{
   return ClassNameRefClauseSyntax {m_root, m_data->getChild(Cursor::ClassNameRef).get()};
}

InstanceofExprSyntax InstanceofExprSyntax::withInstanceExpr(std::optional<ExprSyntax> instanceExpr)
{
   RefCountPtr<RawSyntax> rawInstanceExpr;
   if (instanceExpr.has_value()) {
      rawInstanceExpr = instanceExpr->getRaw();
   } else {
      rawInstanceExpr = RawSyntax::missing(SyntaxKind::InstanceofExpr);
   }
   return m_data->replaceChild<InstanceofExprSyntax>(rawInstanceExpr, Cursor::InstanceExpr);
}

InstanceofExprSyntax InstanceofExprSyntax::withInstanceofToken(std::optional<TokenSyntax> instanceofToken)
{
   RefCountPtr<RawSyntax> rawInstanceof;
   if (instanceofToken.has_value()) {
      rawInstanceof = instanceofToken->getRaw();
   } else {
      rawInstanceof = make_missing_token(T_INSTANCEOF);
   }
   return m_data->replaceChild<InstanceofExprSyntax>(rawInstanceof, Cursor::InstanceofToken);
}

InstanceofExprSyntax InstanceofExprSyntax::withClassNameRef(std::optional<ClassNameRefClauseSyntax> classNameRef)
{
   RefCountPtr<RawSyntax> rawClassNameRef;
   if (classNameRef.has_value()) {
      rawClassNameRef = classNameRef->getRaw();
   } else {
      rawClassNameRef = RawSyntax::missing(SyntaxKind::ClassNameRefClause);
   }
   return m_data->replaceChild<InstanceofExprSyntax>(rawClassNameRef, Cursor::ClassNameRef);
}

///
/// ShellCmdExprSyntax
///
void ShellCmdExprSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ShellCmdExprSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, LeftBacktick, std::set{TokenKindType::T_BACKTICK});
   syntax_assert_child_kind(raw, BackticksExpr, std::set{SyntaxKind::BackticksClause});
   syntax_assert_child_token(raw, RightBacktick, std::set{TokenKindType::T_BACKTICK});
#endif
}

TokenSyntax ShellCmdExprSyntax::getLeftBacktick()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftBacktick).get()};
}

std::optional<BackticksClauseSyntax> ShellCmdExprSyntax::getBackticksExpr()
{
   RefCountPtr<SyntaxData> exprData = m_data->getChild(Cursor::BackticksExpr);
   if (!exprData) {
      return std::nullopt;
   }
   return BackticksClauseSyntax {m_root, exprData.get()};
}

TokenSyntax ShellCmdExprSyntax::getRightBacktick()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightBacktick).get()};
}

ShellCmdExprSyntax ShellCmdExprSyntax::withLeftBacktick(std::optional<TokenSyntax> leftBacktick)
{
   RefCountPtr<RawSyntax> leftBacktickRaw;
   if (leftBacktick.has_value()) {
      leftBacktickRaw = leftBacktick->getRaw();
   } else {
      leftBacktickRaw = make_missing_token(T_BACKTICK);
   }
   return m_data->replaceChild<ShellCmdExprSyntax>(leftBacktickRaw, Cursor::LeftBacktick);
}

ShellCmdExprSyntax ShellCmdExprSyntax::withBackticksExpr(std::optional<BackticksClauseSyntax> backticksExpr)
{
   RefCountPtr<RawSyntax> backticksExprRaw;
   if (backticksExpr.has_value()) {
      backticksExprRaw = backticksExpr->getRaw();
   } else {
      backticksExprRaw = nullptr;
   }
   return m_data->replaceChild<ShellCmdExprSyntax>(backticksExprRaw, Cursor::BackticksExpr);
}

ShellCmdExprSyntax ShellCmdExprSyntax::withRightBacktick(std::optional<TokenSyntax> rightBacktick)
{
   RefCountPtr<RawSyntax> rightBacktickRaw;
   if (rightBacktick.has_value()) {
      rightBacktickRaw = rightBacktick->getRaw();
   } else {
      rightBacktickRaw = make_missing_token(T_BACKTICK);
   }
   return m_data->replaceChild<ShellCmdExprSyntax>(rightBacktickRaw, Cursor::RightBacktick);
}

///
/// UseLexicalVariableClauseSyntax
///
void UseLexicalVariableClauseSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == UseLexicalVariableClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, UseToken, std::set{TokenKindType::T_USE});
   syntax_assert_child_token(raw, LeftParenToken, std::set{TokenKindType::T_LEFT_PAREN});
   syntax_assert_child_kind(raw, LexicalVars, std::set{SyntaxKind::LexicalVarList});
   syntax_assert_child_token(raw, RightParenToken, std::set{TokenKindType::T_RIGHT_PAREN});
#endif
}

TokenSyntax UseLexicalVariableClauseSyntax::getUseToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::UseToken).get()};
}

TokenSyntax UseLexicalVariableClauseSyntax::getLeftParenToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftParenToken).get()};
}

LexicalVariableListSyntax UseLexicalVariableClauseSyntax::getLexicalVars()
{
   return LexicalVariableListSyntax {m_root, m_data->getChild(Cursor::LexicalVars).get()};
}

TokenSyntax UseLexicalVariableClauseSyntax::getRightParenToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::RightParenToken).get()};
}

UseLexicalVariableClauseSyntax
UseLexicalVariableClauseSyntax::withUseToken(std::optional<TokenSyntax> useToken)
{
   RefCountPtr<RawSyntax> useTokenRaw;
   if (useToken.has_value()) {
      useTokenRaw = useToken->getRaw();
   } else {
      useTokenRaw = make_missing_token(T_USE);
   }
   return m_data->replaceChild<UseLexicalVariableClauseSyntax>(useTokenRaw, Cursor::UseToken);
}

UseLexicalVariableClauseSyntax
UseLexicalVariableClauseSyntax::withLeftParenToken(std::optional<TokenSyntax> leftParen)
{
   RefCountPtr<RawSyntax> leftParenRaw;
   if (leftParen.has_value()) {
      leftParenRaw = leftParen->getRaw();
   } else {
      leftParenRaw = make_missing_token(T_LEFT_PAREN);
   }
   return m_data->replaceChild<UseLexicalVariableClauseSyntax>(leftParenRaw, Cursor::UseToken);
}

UseLexicalVariableClauseSyntax
UseLexicalVariableClauseSyntax::withLexicalVars(std::optional<LexicalVariableListSyntax> lexicalVars)
{
   RefCountPtr<RawSyntax> lexicalVarsRaw;
   if (lexicalVars.has_value()) {
      lexicalVarsRaw = lexicalVars->getRaw();
   } else {
      lexicalVarsRaw = RawSyntax::missing(SyntaxKind::LexicalVarList);
   }
   return m_data->replaceChild<UseLexicalVariableClauseSyntax>(lexicalVarsRaw, Cursor::LexicalVars);
}

UseLexicalVariableClauseSyntax
UseLexicalVariableClauseSyntax::withRightParenToken(std::optional<TokenSyntax> rightParen)
{
   RefCountPtr<RawSyntax> rightParenRaw;
   if (rightParen.has_value()) {
      rightParenRaw = rightParen->getRaw();
   } else {
      rightParenRaw = make_missing_token(T_RIGHT_PAREN);
   }
   return m_data->replaceChild<UseLexicalVariableClauseSyntax>(rightParenRaw, Cursor::UseToken);
}

///
/// LexicalVariableSyntax
///
void LexicalVariableSyntax::validate()
{
#ifdef POLAR_DEBUG_BUILD
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == LexicalVariableSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, ReferenceToken, std::set{TokenKindType::T_AMPERSAND});
   syntax_assert_child_token(raw, Variable, std::set{TokenKindType::T_VARIABLE});
#endif
}

std::optional<TokenSyntax> LexicalVariableSyntax::getReferenceToken()
{
   RefCountPtr<SyntaxData> refData = m_data->getChild(Cursor::ReferenceToken);
   if (!refData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, refData.get()};
}

TokenSyntax LexicalVariableSyntax::getVariable()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Variable).get()};
}

LexicalVariableSyntax LexicalVariableSyntax::withReferenceToken(std::optional<TokenSyntax> referenceToken)
{
   RefCountPtr<RawSyntax> referenceTokenRaw;
   if (referenceToken.has_value()) {
      referenceTokenRaw = referenceToken->getRaw();
   } else {
      referenceTokenRaw = nullptr;
   }
   return m_data->replaceChild<LexicalVariableSyntax>(referenceTokenRaw, Cursor::ReferenceToken);
}

LexicalVariableSyntax LexicalVariableSyntax::withVariable(std::optional<TokenSyntax> variable)
{
   RefCountPtr<RawSyntax> variableRaw;
   if (variable.has_value()) {
      variableRaw = variable->getRaw();
   } else {
      variableRaw = make_missing_token(T_VARIABLE);
   }
   return m_data->replaceChild<LexicalVariableSyntax>(variableRaw, Cursor::Variable);
}

///
/// LexicalVariableListItemSyntax
///
void LexicalVariableListItemSyntax::validate()
{

}

std::optional<TokenSyntax>
LexicalVariableListItemSyntax::getComma()
{
   RefCountPtr<SyntaxData> commaData = m_data->getChild(Cursor::Comma);
   if (!commaData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, commaData.get()};
}

LexicalVariableSyntax
LexicalVariableListItemSyntax::getLexicalVariable()
{
   return LexicalVariableSyntax {m_root, m_data->getChild(Cursor::LexicalVariable).get()};
}

LexicalVariableListItemSyntax
LexicalVariableListItemSyntax::withComma(std::optional<TokenSyntax> comma)
{
   RefCountPtr<RawSyntax> rawComma;
   if (comma.has_value()) {
      rawComma = comma->getRaw();
   } else {
      rawComma = nullptr;
   }
   return m_data->replaceChild<LexicalVariableListItemSyntax>(rawComma, Cursor::Comma);
}

LexicalVariableListItemSyntax
LexicalVariableListItemSyntax::withLexicalVariable(std::optional<LexicalVariableSyntax> lexicalVariable)
{
   RefCountPtr<RawSyntax> rawLexicalVariable;
   if (lexicalVariable.has_value()) {
      rawLexicalVariable = lexicalVariable->getRaw();
   } else {
      rawLexicalVariable = RawSyntax::missing(SyntaxKind::LexicalVariable);
   }
   return m_data->replaceChild<LexicalVariableListItemSyntax>(rawLexicalVariable, Cursor::LexicalVariable);
}

} // polar::syntax
