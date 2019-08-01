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

#include "polarphp/syntax/syntaxnode/DeclSyntaxNodes.h"

namespace polar::syntax {

///
/// ReservedNonModifierSyntax
///
void ReservedNonModifierSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == ReservedNonModifierSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, Modifier, CHILD_TOKEN_CHOICES.at(Cursor::Modifier));
}

#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType ReservedNonModifierSyntax::CHILD_TOKEN_CHOICES
{
   {
      ReservedNonModifierSyntax::Modifier, {
         TokenKindType::T_INCLUDE, TokenKindType::T_INCLUDE_ONCE, TokenKindType::T_EVAL,
               TokenKindType::T_REQUIRE, TokenKindType::T_REQUIRE_ONCE, TokenKindType::T_LOGICAL_OR,
               TokenKindType::T_LOGICAL_XOR, TokenKindType::T_LOGICAL_AND, TokenKindType::T_INSTANCEOF,
               TokenKindType::T_NEW, TokenKindType::T_CLONE, TokenKindType::T_EXIT,
               TokenKindType::T_IF, TokenKindType::T_ELSEIF, TokenKindType::T_ELSE, TokenKindType::T_ECHO,
               TokenKindType::T_DO, TokenKindType::T_WHILE, TokenKindType::T_FOR, TokenKindType::T_FOREACH,
               TokenKindType::T_DECLARE, TokenKindType::T_AS, TokenKindType::T_TRY, TokenKindType::T_CATCH,
               TokenKindType::T_FINALLY, TokenKindType::T_THROW, TokenKindType::T_USE, TokenKindType::T_INSTEADOF,
               TokenKindType::T_GLOBAL, TokenKindType::T_VAR, TokenKindType::T_UNSET, TokenKindType::T_ISSET,
               TokenKindType::T_EMPTY, TokenKindType::T_CONTINUE, TokenKindType::T_GOTO, TokenKindType::T_FUNCTION,
               TokenKindType::T_CONST, TokenKindType::T_RETURN, TokenKindType::T_PRINT, TokenKindType::T_YIELD,
               TokenKindType::T_LIST, TokenKindType::T_SWITCH, TokenKindType::T_CASE, TokenKindType::T_DEFAULT,
               TokenKindType::T_BREAK, TokenKindType::T_ARRAY, TokenKindType::T_CALLABLE, TokenKindType::T_EXTENDS,
               TokenKindType::T_IMPLEMENTS, TokenKindType::T_NAMESPACE, TokenKindType::T_TRAIT, TokenKindType::T_INTERFACE,
               TokenKindType::T_CLASS, TokenKindType::T_CLASS_CONST, TokenKindType::T_TRAIT_CONST, TokenKindType::T_FUNC_CONST,
               TokenKindType::T_METHOD_CONST, TokenKindType::T_LINE, TokenKindType::T_FILE, TokenKindType::T_DIR, TokenKindType::T_NS_CONST,
               TokenKindType::T_FN
      }
   }
};
#endif

TokenSyntax ReservedNonModifierSyntax::getModifier()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::Modifier).get()};
}

ReservedNonModifierSyntax ReservedNonModifierSyntax::withModifier(std::optional<TokenSyntax> modifier)
{
   RefCountPtr<RawSyntax> modifierRaw;
   if (modifier.has_value()) {
      modifierRaw = modifier->getRaw();
   } else {
      /// not very good
      modifierRaw = RawSyntax::missing(TokenKindType::T_INCLUDE,
                                       OwnedString::makeUnowned(get_token_text(TokenKindType::T_INCLUDE)));
   }
   return m_data->replaceChild<ReservedNonModifierSyntax>(modifierRaw, Cursor::Modifier);
}

///
/// SemiReservedSytnax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType SemiReservedSytnax::CHILD_TOKEN_CHOICES
{
   {
      SemiReservedSytnax::Cursor::ModifierChoiceToken, {
         TokenKindType::T_STATIC, TokenKindType::T_ABSTRACT, TokenKindType::T_FINAL,
               TokenKindType::T_PRIVATE, TokenKindType::T_PROTECTED, TokenKindType::T_PUBLIC
      }
   }
};
#endif

void SemiReservedSytnax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == SemiReservedSytnax::CHILDREN_COUNT);
   // check node choices
   if (const RefCountPtr<RawSyntax> &modifierChild = raw->getChild(Cursor::Modifier)) {
      if (modifierChild->isToken()) {
         syntax_assert_child_token(raw, ModifierChoiceToken,
                                   CHILD_TOKEN_CHOICES.at(SemiReservedSytnax::ModifierChoiceToken));
         return;
      }
      assert(modifierChild->kindOf(SyntaxKind::ReservedNonModifier));
   }
}

Syntax SemiReservedSytnax::getModifier()
{
   return Syntax{m_root, m_data->getChild(Cursor::Modifier).get()};
}

SemiReservedSytnax SemiReservedSytnax::withModifier(std::optional<Syntax> modifier)
{
   RefCountPtr<RawSyntax> modifierRaw;
   if (modifier.has_value()) {
      modifierRaw = modifier->getRaw();
   } else {
      modifierRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<SemiReservedSytnax>(modifierRaw, Cursor::Modifier);
}

///
/// IdentifierSyntax
///
void IdentifierSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == IdentifierSyntax::CHILDREN_COUNT);
   if (const RefCountPtr<RawSyntax> &itemChild = raw->getChild(Cursor::NameItem)) {
      if (itemChild->isToken()) {
         syntax_assert_child_token(raw, NameItem, std::set{TokenKindType::T_IDENTIFIER_STRING});
         return;
      }
      assert(itemChild->kindOf(SyntaxKind::SemiReserved));
   }
}

Syntax IdentifierSyntax::getNameItem()
{
   return Syntax{m_root, m_data->getChild(Cursor::NameItem).get()};
}

IdentifierSyntax IdentifierSyntax::withNameItem(std::optional<Syntax> item)
{
   RefCountPtr<RawSyntax> nameItemRaw;
   if (item.has_value()) {
      nameItemRaw = item->getRaw();
   } else {
      nameItemRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<IdentifierSyntax>(nameItemRaw, Cursor::NameItem);
}

///
/// NamespacePartSyntax
///
void NamespacePartSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == NamespacePartSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, NsSeparator, std::set{TokenKindType::T_NS_SEPARATOR});
   syntax_assert_child_token(raw, NsSeparator, std::set{TokenKindType::T_IDENTIFIER_STRING});
}

std::optional<TokenSyntax> NamespacePartSyntax::getNsSeparator()
{
   RefCountPtr<SyntaxData> separatorData = m_data->getChild(Cursor::NsSeparator);
   if (!separatorData) {
      return std::nullopt;
   }
   return TokenSyntax{m_root, separatorData.get()};
}

TokenSyntax NamespacePartSyntax::getName()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::Name).get()};
}

NamespacePartSyntax NamespacePartSyntax::withNsSeparator(std::optional<TokenSyntax> separator)
{
   RefCountPtr<RawSyntax> separatorRaw;
   if (separator.has_value()) {
      separatorRaw = separator->getRaw();
   } else {
      separatorRaw = nullptr;
   }
   return m_data->replaceChild<NamespacePartSyntax>(separatorRaw, Cursor::Name);
}

NamespacePartSyntax NamespacePartSyntax::withName(std::optional<TokenSyntax> name)
{
   RefCountPtr<RawSyntax> nameRaw;
   if (name.has_value()) {
      nameRaw = name->getRaw();
   } else {
      nameRaw = RawSyntax::missing(TokenKindType::T_NS_SEPARATOR,
                                   OwnedString::makeUnowned(get_token_text(TokenKindType::T_NS_SEPARATOR)));
   }
   return m_data->replaceChild<NamespacePartSyntax>(nameRaw, Cursor::NsSeparator);
}

///
/// NameSyntax
///
void NameSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == NameSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, NsToken, std::set{TokenKindType::T_NAMESPACE});
   syntax_assert_child_token(raw, NsSeparator, std::set{TokenKindType::T_NS_SEPARATOR});
   if (const RefCountPtr<RawSyntax> &nsChild = raw->getChild(Cursor::Namespace)) {
      assert(nsChild->kindOf(SyntaxKind::NamespacePartList));
   }
}

std::optional<TokenSyntax> NameSyntax::getNsToken()
{
   RefCountPtr<SyntaxData> nsTokenData = m_data->getChild(Cursor::NsToken);
   if (!nsTokenData) {
      return std::nullopt;
   }
   return TokenSyntax{m_root, nsTokenData.get()};
}

std::optional<TokenSyntax> NameSyntax::getNsSeparator()
{
   RefCountPtr<SyntaxData> separatorData = m_data->getChild(Cursor::NsSeparator);
   if (!separatorData) {
      return std::nullopt;
   }
   return TokenSyntax{m_root, separatorData.get()};
}

NamespacePartListSyntax NameSyntax::getNamespace()
{
   return NamespacePartListSyntax{m_root, m_data->getChild(Cursor::Namespace).get()};
}

NameSyntax NameSyntax::withNsToken(std::optional<TokenSyntax> nsToken)
{
   RefCountPtr<RawSyntax> nsTokenRaw;
   if (nsToken.has_value()) {
      nsTokenRaw = nsToken->getRaw();
   } else {
      nsTokenRaw = nullptr;
   }
   return m_data->replaceChild<NameSyntax>(nsTokenRaw, Cursor::NsToken);
}

NameSyntax NameSyntax::withNsSeparator(std::optional<TokenSyntax> separatorToken)
{
   RefCountPtr<RawSyntax> separatorTokenRaw;
   if (separatorToken.has_value()) {
      separatorTokenRaw = separatorToken->getRaw();
   } else {
      separatorTokenRaw = nullptr;
   }
   return m_data->replaceChild<NameSyntax>(separatorTokenRaw, Cursor::NsSeparator);
}

NameSyntax NameSyntax::withNamespace(std::optional<NamespacePartListSyntax> ns)
{
   RefCountPtr<RawSyntax> nsRaw;
   if (ns.has_value()) {
      nsRaw = ns->getRaw();
   } else {
      nsRaw = RawSyntax::missing(SyntaxKind::NamespacePartList);
   }
   return m_data->replaceChild<NameSyntax>(nsRaw, Cursor::Namespace);
}

NameSyntax NameSyntax::addNamespacePart(NamespacePartSyntax namespacePart)
{
   RefCountPtr<RawSyntax> namespaces = getRaw()->getChild(Cursor::Namespace);
   if (namespaces) {
      namespaces = namespaces->append(namespacePart.getRaw());
   } else {
      namespaces = RawSyntax::make(SyntaxKind::NamespacePartList, {namespacePart.getRaw()}, SourcePresence::Present);
   }
   return m_data->replaceChild<NameSyntax>(namespaces, Cursor::Namespace);
}

///
/// NamespaceUseTypeSyntax
///
#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType NamespaceUseTypeSyntax::CHILD_TOKEN_CHOICES
{
   {
      NamespaceUseTypeSyntax::TypeToken, {
         TokenKindType::T_FUNCTION, TokenKindType::T_CONST
      }
   }
};
#endif

void NamespaceUseTypeSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == NamespaceUseTypeSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, TypeToken, CHILD_TOKEN_CHOICES.at(Cursor::TypeToken));
}

TokenSyntax NamespaceUseTypeSyntax::getTypeToken()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::TypeToken).get()};
}

NamespaceUseTypeSyntax NamespaceUseTypeSyntax::withTypeToken(std::optional<TokenSyntax> typeToken)
{
   RefCountPtr<RawSyntax> typeTokenRaw;
   if (typeToken.has_value()) {
      typeTokenRaw = typeToken->getRaw();
   } else {
      typeTokenRaw = RawSyntax::missing(TokenKindType::T_FUNCTION,
                                        OwnedString::makeUnowned(get_token_text(TokenKindType::T_FUNCTION)));
   }
   return m_data->replaceChild<NamespaceUseTypeSyntax>(typeTokenRaw, Cursor::TypeToken);
}

///
/// NamespaceUnprefixedUseDeclarationSyntax
///
void NamespaceUnprefixedUseDeclarationSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == NamespaceUnprefixedUseDeclarationSyntax::CHILDREN_COUNT);
   if (const RefCountPtr<RawSyntax> &nsChild = raw->getChild(Cursor::Namespace)) {
      assert(nsChild->kindOf(SyntaxKind::NamespacePartList));
   }
   syntax_assert_child_token(raw, AsToken, std::set{TokenKindType::T_AS});
   syntax_assert_child_token(raw, IdentifierToken, std::set{TokenKindType::T_IDENTIFIER_STRING});
}

NamespacePartListSyntax NamespaceUnprefixedUseDeclarationSyntax::getNamespace()
{
   return NamespacePartListSyntax{m_root, m_data->getChild(Cursor::Namespace).get()};
}

std::optional<TokenSyntax> NamespaceUnprefixedUseDeclarationSyntax::getAsToken()
{
   RefCountPtr<SyntaxData> asTokenData = m_data->getChild(Cursor::AsToken);
   if (!asTokenData) {
      return std::nullopt;
   }
   return TokenSyntax{m_root, asTokenData.get()};
}

std::optional<TokenSyntax> NamespaceUnprefixedUseDeclarationSyntax::getIdentifierToken()
{
   RefCountPtr<SyntaxData> identifierData = m_data->getChild(Cursor::IdentifierToken);
   if (!identifierData) {
      return std::nullopt;
   }
   return TokenSyntax{m_root, identifierData.get()};
}

NamespaceUnprefixedUseDeclarationSyntax
NamespaceUnprefixedUseDeclarationSyntax::addNamespacePart(NamespacePartSyntax namespacePart)
{
   RefCountPtr<RawSyntax> namespacesRaw = getRaw()->getChild(Cursor::Namespace);
   if (namespacesRaw) {
      namespacesRaw = namespacesRaw->append(namespacePart.getRaw());
   } else {
      namespacesRaw = RawSyntax::make(SyntaxKind::NamespacePartList, {namespacePart.getRaw()},
                                      SourcePresence::Present);
   }
   return m_data->replaceChild<NamespaceUnprefixedUseDeclarationSyntax>(namespacesRaw, Cursor::Namespace);
}

NamespaceUnprefixedUseDeclarationSyntax
NamespaceUnprefixedUseDeclarationSyntax::withNamespace(std::optional<NamespacePartListSyntax> ns)
{
   RefCountPtr<RawSyntax> nsRaw;
   if (ns.has_value()) {
      nsRaw = ns->getRaw();
   } else {
      nsRaw = RawSyntax::missing(SyntaxKind::NamespacePartList);
   }
   return m_data->replaceChild<NamespaceUnprefixedUseDeclarationSyntax>(nsRaw, Cursor::Namespace);
}

NamespaceUnprefixedUseDeclarationSyntax
NamespaceUnprefixedUseDeclarationSyntax::withAsToken(std::optional<TokenSyntax> asToken)
{
   RefCountPtr<RawSyntax> asTokenRaw;
   if (asToken.has_value()) {
      asTokenRaw = asToken->getRaw();
   } else {
      asTokenRaw = nullptr;
   }
   return m_data->replaceChild<NamespaceUnprefixedUseDeclarationSyntax>(asTokenRaw, Cursor::AsToken);
}

NamespaceUnprefixedUseDeclarationSyntax
NamespaceUnprefixedUseDeclarationSyntax::withIdentifierToken(std::optional<TokenSyntax> identifierToken)
{
   RefCountPtr<RawSyntax> identifierTokenRaw;
   if (identifierToken.has_value()) {
      identifierTokenRaw = identifierToken->getRaw();
   } else {
      identifierTokenRaw = nullptr;
   }
   return m_data->replaceChild<NamespaceUnprefixedUseDeclarationSyntax>(identifierTokenRaw, Cursor::IdentifierToken);
}

///
/// NamespaceUseDeclarationSyntax
///
void NamespaceUseDeclarationSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == NamespaceUseDeclarationSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, NsSeparator, std::set{TokenKindType::T_NS_SEPARATOR});
   if (const RefCountPtr<RawSyntax> &declarationChild = raw->getChild(Cursor::UnprefixedUseDeclaration)) {
      assert(declarationChild->kindOf(SyntaxKind::NamespaceUnprefixedUseDeclaration));
   }
}

std::optional<TokenSyntax> NamespaceUseDeclarationSyntax::getNsSeparator()
{
   RefCountPtr<SyntaxData> separatorData = m_data->getChild(Cursor::NsSeparator);
   if (!separatorData) {
      return std::nullopt;
   }
   return TokenSyntax{m_root, separatorData.get()};
}

NamespaceUnprefixedUseDeclarationSyntax
NamespaceUseDeclarationSyntax::getUnprefixedUseDeclaration()
{
   return NamespaceUnprefixedUseDeclarationSyntax{m_root, m_data->getChild(Cursor::UnprefixedUseDeclaration).get()};
}

NamespaceUseDeclarationSyntax
NamespaceUseDeclarationSyntax::withNsSeparator(std::optional<TokenSyntax> nsSeparator)
{
   RefCountPtr<RawSyntax> nsSeparatorRaw;
   if (nsSeparator.has_value()) {
      nsSeparatorRaw = nsSeparator->getRaw();
   } else {
      nsSeparatorRaw = nullptr;
   }
   return m_data->replaceChild<NamespaceUseDeclarationSyntax>(nsSeparatorRaw, Cursor::NsSeparator);
}

NamespaceUseDeclarationSyntax
NamespaceUseDeclarationSyntax::withUnprefixedUseDeclaration(std::optional<NamespaceUnprefixedUseDeclarationSyntax> declaration)
{
   RefCountPtr<RawSyntax> declarationRaw;
   if (declaration.has_value()) {
      declarationRaw = declaration->getRaw();
   } else {
      declarationRaw = RawSyntax::missing(SyntaxKind::NamespaceUnprefixedUseDeclaration);
   }
   return m_data->replaceChild<NamespaceUseDeclarationSyntax>(declarationRaw, Cursor::UnprefixedUseDeclaration);
}

///
/// NamespaceInlineUseDeclarationSyntax
///
void NamespaceInlineUseDeclarationSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == NamespaceInlineUseDeclarationSyntax::CHILDREN_COUNT);
   if (const RefCountPtr<RawSyntax> &useTypeChild = raw->getChild(Cursor::UseType)) {
      assert(useTypeChild->kindOf(SyntaxKind::NamespaceUseType));
   }
   if (const RefCountPtr<RawSyntax> &declarationChild = raw->getChild(Cursor::UnprefixedUseDeclaration)) {
      assert(declarationChild->kindOf(SyntaxKind::NamespaceUnprefixedUseDeclaration));
   }
}

std::optional<NamespaceUseTypeSyntax> NamespaceInlineUseDeclarationSyntax::getUseType()
{
   RefCountPtr<SyntaxData> useTypeData = m_data->getChild(Cursor::UseType);
   if (!useTypeData) {
      return std::nullopt;
   }
   return NamespaceUseTypeSyntax{m_root, useTypeData.get()};
}

NamespaceUnprefixedUseDeclarationSyntax
NamespaceInlineUseDeclarationSyntax::getUnprefixedUseDeclaration()
{
   return NamespaceUnprefixedUseDeclarationSyntax{m_root, m_data->getChild(Cursor::UnprefixedUseDeclaration).get()};
}

NamespaceInlineUseDeclarationSyntax
NamespaceInlineUseDeclarationSyntax::withUseType(std::optional<NamespaceUseTypeSyntax> useType)
{
   RefCountPtr<RawSyntax> useTypeRaw;
   if (useType.has_value()) {
      useTypeRaw = useType->getRaw();
   } else {
      useTypeRaw = nullptr;
   }
   return m_data->replaceChild<NamespaceInlineUseDeclarationSyntax>(useTypeRaw, Cursor::UseType);
}

NamespaceInlineUseDeclarationSyntax
NamespaceInlineUseDeclarationSyntax::withUnprefixedUseDeclaration(std::optional<NamespaceUnprefixedUseDeclarationSyntax> declaration)
{
   RefCountPtr<RawSyntax> declarationRaw;
   if (declaration.has_value()) {
      declarationRaw = declaration->getRaw();
   } else {
      declarationRaw = RawSyntax::missing(SyntaxKind::NamespaceUnprefixedUseDeclaration);
   }
   return m_data->replaceChild<NamespaceInlineUseDeclarationSyntax>(declarationRaw, Cursor::UnprefixedUseDeclaration);
}

///
/// NamespaceGroupUseDeclarationSyntax
///
void NamespaceGroupUseDeclarationSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == NamespaceGroupUseDeclarationSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, FirstNsSeparator, std::set{TokenKindType::T_NS_SEPARATOR});
   syntax_assert_child_token(raw, SecondNsSeparator, std::set{TokenKindType::T_NS_SEPARATOR});
   syntax_assert_child_token(raw, LeftBrace, std::set{TokenKindType::T_LEFT_BRACE});
   syntax_assert_child_token(raw, LeftBrace, std::set{TokenKindType::T_RIGHT_BRACE});
   syntax_assert_child_token(raw, CommaToken, std::set{TokenKindType::T_COMMA});
   if (const RefCountPtr<RawSyntax> &namespaceChild = raw->getChild(Cursor::Namespace)) {
      assert(namespaceChild->kindOf(SyntaxKind::NamespacePartList));
   }
   if (const RefCountPtr<RawSyntax> &declarationsChild = raw->getChild(Cursor::UnprefixedUseDeclarations)) {
      assert(declarationsChild->kindOf(SyntaxKind::NamespaceUnprefixedUseDeclarationList));
   }
}

std::optional<TokenSyntax> NamespaceGroupUseDeclarationSyntax::getFirstNsSeparator()
{
   RefCountPtr<SyntaxData> separatorData = m_data->getChild(Cursor::FirstNsSeparator);
   if (!separatorData) {
      return std::nullopt;
   }
   return TokenSyntax{m_root, separatorData.get()};
}

NamespacePartListSyntax NamespaceGroupUseDeclarationSyntax::getNamespace()
{
   return NamespacePartListSyntax{m_root, m_data->getChild(Cursor::Namespace).get()};
}

TokenSyntax NamespaceGroupUseDeclarationSyntax::getSecondNsSeparator()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::SecondNsSeparator).get()};
}

TokenSyntax NamespaceGroupUseDeclarationSyntax::getLeftBrace()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftBrace).get()};
}

NamespaceUnprefixedUseDeclarationListSyntax
NamespaceGroupUseDeclarationSyntax::getUnprefixedUseDeclarations()
{
   return NamespaceUnprefixedUseDeclarationListSyntax {m_root, m_data->getChild(Cursor::UnprefixedUseDeclarations).get()};
}

std::optional<TokenSyntax> NamespaceGroupUseDeclarationSyntax::getCommaToken()
{
   RefCountPtr<SyntaxData> commaData = m_data->getChild(Cursor::CommaToken);
   if (!commaData) {
      return std::nullopt;
   }
   return TokenSyntax{m_root, commaData.get()};
}

TokenSyntax NamespaceGroupUseDeclarationSyntax::getRightBrace()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::LeftBrace).get()};
}

NamespaceGroupUseDeclarationSyntax
NamespaceGroupUseDeclarationSyntax::withFirstNsSeparator(std::optional<TokenSyntax> separator)
{
   RefCountPtr<RawSyntax> separatorRaw;
   if (separator.has_value()) {
      separatorRaw = separator->getRaw();
   } else {
      separatorRaw = nullptr;
   }
   return m_data->replaceChild<NamespaceGroupUseDeclarationSyntax>(separatorRaw, Cursor::FirstNsSeparator);
}

NamespaceGroupUseDeclarationSyntax
NamespaceGroupUseDeclarationSyntax::withNamespace(std::optional<NamespacePartListSyntax> ns)
{
   RefCountPtr<RawSyntax> nsRaw;
   if (ns.has_value()) {
      nsRaw = ns->getRaw();
   } else {
      nsRaw = RawSyntax::missing(SyntaxKind::NamespacePartList);
   }
   return m_data->replaceChild<NamespaceGroupUseDeclarationSyntax>(nsRaw, Cursor::Namespace);
}

NamespaceGroupUseDeclarationSyntax
NamespaceGroupUseDeclarationSyntax::withSecondNsSeparator(std::optional<TokenSyntax> separator)
{
   RefCountPtr<RawSyntax> separatorRaw;
   if (separator.has_value()) {
      separatorRaw = separator->getRaw();
   } else {
      separatorRaw = RawSyntax::missing(TokenKindType::T_NS_SEPARATOR,
                                        OwnedString::makeUnowned(get_token_text(TokenKindType::T_NS_SEPARATOR)));
   }
   return m_data->replaceChild<NamespaceGroupUseDeclarationSyntax>(separatorRaw, Cursor::SecondNsSeparator);
}

NamespaceGroupUseDeclarationSyntax
NamespaceGroupUseDeclarationSyntax::withLeftBrace(std::optional<TokenSyntax> leftBrace)
{
   RefCountPtr<RawSyntax> leftBraceRaw;
   if (leftBrace.has_value()) {
      leftBraceRaw = leftBrace->getRaw();
   } else {
      leftBraceRaw = RawSyntax::missing(TokenKindType::T_LEFT_BRACE,
                                        OwnedString::makeUnowned(get_token_text(TokenKindType::T_LEFT_BRACE)));
   }
   return m_data->replaceChild<NamespaceGroupUseDeclarationSyntax>(leftBraceRaw, Cursor::LeftBrace);
}

NamespaceGroupUseDeclarationSyntax
NamespaceGroupUseDeclarationSyntax::withUnprefixedUseDeclarations(std::optional<NamespaceUnprefixedUseDeclarationListSyntax> declarations)
{
   RefCountPtr<RawSyntax> declarationsRaw;
   if (declarations.has_value()) {
      declarationsRaw = declarations->getRaw();
   } else {
      declarationsRaw = RawSyntax::missing(SyntaxKind::NamespaceUnprefixedUseDeclarationList);
   }
   return m_data->replaceChild<NamespaceGroupUseDeclarationSyntax>(declarationsRaw, Cursor::UnprefixedUseDeclarations);
}

NamespaceGroupUseDeclarationSyntax
NamespaceGroupUseDeclarationSyntax::withCommaToken(std::optional<TokenSyntax> comma)
{
   RefCountPtr<RawSyntax> commaRaw;
   if (comma.has_value()) {
      commaRaw = comma->getRaw();
   } else {
      commaRaw = RawSyntax::missing(TokenKindType::T_COMMA,
                                    OwnedString::makeUnowned(get_token_text(TokenKindType::T_COMMA)));
   }
   return m_data->replaceChild<NamespaceGroupUseDeclarationSyntax>(commaRaw, Cursor::CommaToken);
}

NamespaceGroupUseDeclarationSyntax
NamespaceGroupUseDeclarationSyntax::withRightBrace(std::optional<TokenSyntax> rightBrace)
{
   RefCountPtr<RawSyntax> rightBraceRaw;
   if (rightBrace.has_value()) {
      rightBraceRaw = rightBrace->getRaw();
   } else {
      rightBraceRaw = RawSyntax::missing(TokenKindType::T_RIGHT_BRACE,
                                         OwnedString::makeUnowned(get_token_text(TokenKindType::T_RIGHT_BRACE)));
   }
   return m_data->replaceChild<NamespaceGroupUseDeclarationSyntax>(rightBraceRaw, Cursor::RightBrace);
}

NamespaceGroupUseDeclarationSyntax
NamespaceGroupUseDeclarationSyntax::addUnprefixedUseDeclaration(NamespaceUnprefixedUseDeclarationSyntax declaration)
{
   RefCountPtr<RawSyntax> declarationsRaw = getRaw()->getChild(Cursor::UnprefixedUseDeclarations);
   if (declarationsRaw) {
      declarationsRaw = declarationsRaw->append(declaration.getRaw());
   } else {
      declarationsRaw = RawSyntax::make(SyntaxKind::NamespaceUnprefixedUseDeclarationList, {
                                           declaration.getRaw()
                                        }, SourcePresence::Present);
   }
   return m_data->replaceChild<NamespaceGroupUseDeclarationSyntax>(declarationsRaw, Cursor::UnprefixedUseDeclarations);
}

///
/// NamespaceMixedGroupUseDeclarationSyntax
///
void NamespaceMixedGroupUseDeclarationSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == NamespaceMixedGroupUseDeclarationSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, FirstNsSeparator, std::set{TokenKindType::T_NS_SEPARATOR});
   syntax_assert_child_token(raw, SecondNsSeparator, std::set{TokenKindType::T_NS_SEPARATOR});
   syntax_assert_child_token(raw, LeftBrace, std::set{TokenKindType::T_LEFT_BRACE});
   syntax_assert_child_token(raw, LeftBrace, std::set{TokenKindType::T_RIGHT_BRACE});
   syntax_assert_child_token(raw, CommaToken, std::set{TokenKindType::T_COMMA});
   if (const RefCountPtr<RawSyntax> &namespaceChild = raw->getChild(Cursor::Namespace)) {
      assert(namespaceChild->kindOf(SyntaxKind::NamespacePartList));
   }
   if (const RefCountPtr<RawSyntax> &declarationsChild = raw->getChild(Cursor::InlineUseDeclarations)) {
      assert(declarationsChild->kindOf(SyntaxKind::NamespaceInlineUseDeclarationList));
   }
}

std::optional<TokenSyntax> NamespaceMixedGroupUseDeclarationSyntax::getFirstNsSeparator()
{
   RefCountPtr<SyntaxData> separatorData = m_data->getChild(Cursor::FirstNsSeparator);
   if (!separatorData) {
      return std::nullopt;
   }
   return TokenSyntax{m_root, separatorData.get()};
}

NamespacePartListSyntax NamespaceMixedGroupUseDeclarationSyntax::getNamespace()
{
   return NamespacePartListSyntax{m_root, m_data->getChild(Cursor::Namespace).get()};
}

TokenSyntax NamespaceMixedGroupUseDeclarationSyntax::getSecondNsSeparator()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::SecondNsSeparator).get()};
}

TokenSyntax NamespaceMixedGroupUseDeclarationSyntax::getLeftBrace()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftBrace).get()};
}

NamespaceInlineUseDeclarationListSyntax
NamespaceMixedGroupUseDeclarationSyntax::getInlineUseDeclarations()
{
   return NamespaceInlineUseDeclarationListSyntax {m_root, m_data->getChild(Cursor::InlineUseDeclarations).get()};
}

std::optional<TokenSyntax> NamespaceMixedGroupUseDeclarationSyntax::getCommaToken()
{
   RefCountPtr<SyntaxData> commaData = m_data->getChild(Cursor::CommaToken);
   if (!commaData) {
      return std::nullopt;
   }
   return TokenSyntax{m_root, commaData.get()};
}

TokenSyntax NamespaceMixedGroupUseDeclarationSyntax::getRightBrace()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::LeftBrace).get()};
}

NamespaceMixedGroupUseDeclarationSyntax
NamespaceMixedGroupUseDeclarationSyntax::withFirstNsSeparator(std::optional<TokenSyntax> separator)
{
   RefCountPtr<RawSyntax> separatorRaw;
   if (separator.has_value()) {
      separatorRaw = separator->getRaw();
   } else {
      separatorRaw = nullptr;
   }
   return m_data->replaceChild<NamespaceMixedGroupUseDeclarationSyntax>(separatorRaw, Cursor::FirstNsSeparator);
}

NamespaceMixedGroupUseDeclarationSyntax
NamespaceMixedGroupUseDeclarationSyntax::withNamespace(std::optional<NamespacePartListSyntax> ns)
{
   RefCountPtr<RawSyntax> nsRaw;
   if (ns.has_value()) {
      nsRaw = ns->getRaw();
   } else {
      nsRaw = RawSyntax::missing(SyntaxKind::NamespacePartList);
   }
   return m_data->replaceChild<NamespaceMixedGroupUseDeclarationSyntax>(nsRaw, Cursor::Namespace);
}

NamespaceMixedGroupUseDeclarationSyntax
NamespaceMixedGroupUseDeclarationSyntax::withSecondNsSeparator(std::optional<TokenSyntax> separator)
{
   RefCountPtr<RawSyntax> separatorRaw;
   if (separator.has_value()) {
      separatorRaw = separator->getRaw();
   } else {
      separatorRaw = RawSyntax::missing(TokenKindType::T_NS_SEPARATOR,
                                        OwnedString::makeUnowned(get_token_text(TokenKindType::T_NS_SEPARATOR)));
   }
   return m_data->replaceChild<NamespaceMixedGroupUseDeclarationSyntax>(separatorRaw, Cursor::SecondNsSeparator);
}

NamespaceMixedGroupUseDeclarationSyntax
NamespaceMixedGroupUseDeclarationSyntax::withLeftBrace(std::optional<TokenSyntax> leftBrace)
{
   RefCountPtr<RawSyntax> leftBraceRaw;
   if (leftBrace.has_value()) {
      leftBraceRaw = leftBrace->getRaw();
   } else {
      leftBraceRaw = RawSyntax::missing(TokenKindType::T_LEFT_BRACE,
                                        OwnedString::makeUnowned(get_token_text(TokenKindType::T_LEFT_BRACE)));
   }
   return m_data->replaceChild<NamespaceMixedGroupUseDeclarationSyntax>(leftBraceRaw, Cursor::LeftBrace);
}

NamespaceMixedGroupUseDeclarationSyntax
NamespaceMixedGroupUseDeclarationSyntax::withInlineUseDeclarations(std::optional<NamespaceInlineUseDeclarationListSyntax> declarations)
{
   RefCountPtr<RawSyntax> declarationsRaw;
   if (declarations.has_value()) {
      declarationsRaw = declarations->getRaw();
   } else {
      declarationsRaw = RawSyntax::missing(SyntaxKind::NamespaceInlineUseDeclarationList);
   }
   return m_data->replaceChild<NamespaceMixedGroupUseDeclarationSyntax>(declarationsRaw, Cursor::InlineUseDeclarations);
}

NamespaceMixedGroupUseDeclarationSyntax
NamespaceMixedGroupUseDeclarationSyntax::withCommaToken(std::optional<TokenSyntax> comma)
{
   RefCountPtr<RawSyntax> commaRaw;
   if (comma.has_value()) {
      commaRaw = comma->getRaw();
   } else {
      commaRaw = RawSyntax::missing(TokenKindType::T_COMMA,
                                    OwnedString::makeUnowned(get_token_text(TokenKindType::T_COMMA)));
   }
   return m_data->replaceChild<NamespaceMixedGroupUseDeclarationSyntax>(commaRaw, Cursor::CommaToken);
}

NamespaceMixedGroupUseDeclarationSyntax
NamespaceMixedGroupUseDeclarationSyntax::withRightBrace(std::optional<TokenSyntax> rightBrace)
{
   RefCountPtr<RawSyntax> rightBraceRaw;
   if (rightBrace.has_value()) {
      rightBraceRaw = rightBrace->getRaw();
   } else {
      rightBraceRaw = RawSyntax::missing(TokenKindType::T_RIGHT_BRACE,
                                         OwnedString::makeUnowned(get_token_text(TokenKindType::T_RIGHT_BRACE)));
   }
   return m_data->replaceChild<NamespaceMixedGroupUseDeclarationSyntax>(rightBraceRaw, Cursor::RightBrace);
}

NamespaceMixedGroupUseDeclarationSyntax
NamespaceMixedGroupUseDeclarationSyntax::addInlineUseDeclaration(NamespaceInlineUseDeclarationSyntax declaration)
{
   RefCountPtr<RawSyntax> declarationsRaw = getRaw()->getChild(Cursor::InlineUseDeclarations);
   if (declarationsRaw) {
      declarationsRaw = declarationsRaw->append(declaration.getRaw());
   } else {
      declarationsRaw = RawSyntax::make(SyntaxKind::NamespaceUnprefixedUseDeclarationList, {
                                           declaration.getRaw()
                                        }, SourcePresence::Present);
   }
   return m_data->replaceChild<NamespaceMixedGroupUseDeclarationSyntax>(declarationsRaw, Cursor::InlineUseDeclarations);
}

///
/// NamespaceUseSyntax
///
void NamespaceUseSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == NamespaceUseSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, UseToken, std::set{TokenKindType::T_USE});
   syntax_assert_child_token(raw, SemicolonToken, std::set{TokenKindType::T_SEMICOLON});
   if (const RefCountPtr<RawSyntax> &useTypeChild = raw->getChild(Cursor::UseType)) {
      assert(useTypeChild->kindOf(SyntaxKind::NamespaceUseType));
   }
   if (const RefCountPtr<RawSyntax> &declarationsChild = raw->getChild(Cursor::Declarations)) {
      bool isMixGroupUseDeclarations = declarationsChild->kindOf(SyntaxKind::NamespacemixedGroupUseDeclaration);
      bool isGroupUseDeclarations = declarationsChild->kindOf(SyntaxKind::NamespaceGroupUseDeclaration);
      bool isUseDeclarations = declarationsChild->kindOf(SyntaxKind::NamespaceUseDeclarationList);
      assert(isMixGroupUseDeclarations || isGroupUseDeclarations || isUseDeclarations);
   }
}

TokenSyntax NamespaceUseSyntax::getUseToken()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::UseToken).get()};
}

std::optional<NamespaceUseTypeSyntax>
NamespaceUseSyntax::getUseType()
{
   RefCountPtr<SyntaxData> useTypeData = m_data->getChild(Cursor::UseType);
   if (!useTypeData) {
      return std::nullopt;
   }
   return NamespaceUseTypeSyntax{m_root, useTypeData.get()};
}

Syntax NamespaceUseSyntax::getDeclarations()
{
   return Syntax {m_root, m_data->getChild(Cursor::Declarations).get()};
}

TokenSyntax NamespaceUseSyntax::getSemicolon()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::SemicolonToken).get()};
}

NamespaceUseSyntax
NamespaceUseSyntax::withUseToken(std::optional<TokenSyntax> useToken)
{
   RefCountPtr<RawSyntax> useTokenRaw;
   if (useToken.has_value()) {
      useTokenRaw = useToken->getRaw();
   } else {
      useTokenRaw = RawSyntax::missing(TokenKindType::T_USE,
                                       OwnedString::makeUnowned(get_token_text(TokenKindType::T_USE)));
   }
   return m_data->replaceChild<NamespaceUseSyntax>(useTokenRaw, Cursor::UseToken);
}

NamespaceUseSyntax
NamespaceUseSyntax::withUseType(std::optional<NamespaceUseTypeSyntax> useType)
{
   RefCountPtr<RawSyntax> useTypeRaw;
   if (useType.has_value()) {
      useTypeRaw = useType->getRaw();
   } else {
      useTypeRaw = nullptr;
   }
   return m_data->replaceChild<NamespaceUseSyntax>(useTypeRaw, Cursor::UseType);
}

NamespaceUseSyntax
NamespaceUseSyntax::withDeclarations(std::optional<Syntax> declarations)
{
   RefCountPtr<RawSyntax> declarationsRaw;
   if (declarations.has_value()) {
      declarationsRaw = declarations->getRaw();
   } else {
      declarationsRaw = RawSyntax::missing(SyntaxKind::NamespaceUseDeclarationList);
   }
   return m_data->replaceChild<NamespaceUseSyntax>(declarationsRaw, Cursor::Declarations);
}

NamespaceUseSyntax
NamespaceUseSyntax::withSemicolonToken(std::optional<TokenSyntax> semicolon)
{
   RefCountPtr<RawSyntax> tokenRaw;
   if (semicolon.has_value()) {
      tokenRaw = semicolon->getRaw();
   } else {
      tokenRaw = RawSyntax::missing(TokenKindType::T_SEMICOLON,
                                    OwnedString::makeUnowned(get_token_text(TokenKindType::T_SEMICOLON)));
   }
   return m_data->replaceChild<NamespaceUseSyntax>(tokenRaw, Cursor::SemicolonToken);
}

///
/// InitializeClauseSyntax
///
void InitializeClauseSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == InitializeClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, EqualToken, std::set{TokenKindType::T_EQUAL});
   if (const RefCountPtr<RawSyntax> valueExpr = raw->getChild(Cursor::ValueExpr)) {
      valueExpr->kindOf(SyntaxKind::Expr);
   }
}

TokenSyntax InitializeClauseSyntax::getEqualToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::EqualToken).get()};
}

ExprSyntax InitializeClauseSyntax::getValueExpr()
{
   return ExprSyntax {m_root, m_data->getChild(Cursor::ValueExpr).get()};
}

InitializeClauseSyntax InitializeClauseSyntax::withEqualToken(std::optional<TokenSyntax> equalToken)
{
   RefCountPtr<RawSyntax> equalTokenRaw;
   if (equalToken.has_value()) {
      equalTokenRaw = equalToken->getRaw();
   } else {
      equalTokenRaw = RawSyntax::missing(TokenKindType::T_EQUAL,
                                         OwnedString::makeUnowned(get_token_text(TokenKindType::T_EQUAL)));
   }
   return m_data->replaceChild<InitializeClauseSyntax>(equalTokenRaw, Cursor::EqualToken);
}

InitializeClauseSyntax InitializeClauseSyntax::withValueExpr(std::optional<ExprSyntax> valueExpr)
{
   RefCountPtr<RawSyntax> valueExprRaw;
   if (valueExpr.has_value()) {
      valueExprRaw = valueExpr->getRaw();
   } else {
      valueExprRaw = RawSyntax::missing(SyntaxKind::UnknownExpr);
   }
   return m_data->replaceChild<InitializeClauseSyntax>(valueExprRaw, Cursor::ValueExpr);
}

///
/// ConstDeclareItemSyntax
///
void ConstDeclareItemSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == ConstDeclareItemSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, Name, std::set{TokenKindType::T_IDENTIFIER_STRING});
   if (const RefCountPtr<RawSyntax> &initializerChild = raw->getChild(Cursor::InitializerClause)) {
      initializerChild->kindOf(SyntaxKind::InitializeClause);
   }
}

TokenSyntax ConstDeclareItemSyntax::getName()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Name).get()};
}

InitializeClauseSyntax ConstDeclareItemSyntax::getInitializer()
{
   return InitializeClauseSyntax {m_root, m_data->getChild(Cursor::InitializerClause).get()};
}

ConstDeclareItemSyntax ConstDeclareItemSyntax::withName(std::optional<TokenSyntax> name)
{
   RefCountPtr<RawSyntax> nameRaw;
   if (name.has_value()) {
      nameRaw = name->getRaw();
   } else {
      nameRaw = RawSyntax::missing(TokenKindType::T_IDENTIFIER_STRING,
                                   OwnedString::makeUnowned(get_token_text(TokenKindType::T_IDENTIFIER_STRING)));
   }
   return m_data->replaceChild<ConstDeclareItemSyntax>(nameRaw, Cursor::Name);
}

ConstDeclareItemSyntax ConstDeclareItemSyntax::withIntializer(std::optional<InitializeClauseSyntax> initializer)
{
   RefCountPtr<RawSyntax> initializerRaw;
   if (initializer.has_value()) {
      initializerRaw = initializer->getRaw();
   } else {
      initializerRaw = RawSyntax::missing(SyntaxKind::InitializeClause);
   }
   return m_data->replaceChild<ConstDeclareItemSyntax>(initializerRaw, Cursor::InitializerClause);
}

///
/// ConstDefinitionSyntax
///
void ConstDefinitionSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == ConstDefinitionSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, ConstToken, std::set{TokenKindType::T_CONST});
   syntax_assert_child_token(raw, Semicolon, std::set{TokenKindType::T_SEMICOLON});
   if (const RefCountPtr<RawSyntax> &declarations = raw->getChild(Cursor::Declarations)) {
      assert(declarations->kindOf(SyntaxKind::ConstDeclareItemList));
   }
}

TokenSyntax ConstDefinitionSyntax::getConstToken()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::ConstToken).get()};
}

ConstDeclareItemListSyntax ConstDefinitionSyntax::getDeclarations()
{
   return ConstDeclareItemListSyntax {m_root, m_data->getChild(Cursor::Declarations).get()};
}

TokenSyntax ConstDefinitionSyntax::getSemicolon()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Semicolon).get()};
}

ConstDefinitionSyntax ConstDefinitionSyntax::withConstToken(std::optional<TokenSyntax> constToken)
{
   RefCountPtr<RawSyntax> constTokenRaw;
   if (constToken.has_value()) {
      constTokenRaw = constToken->getRaw();
   } else {
      constTokenRaw = RawSyntax::missing(TokenKindType::T_CONST,
                                         OwnedString::makeUnowned(get_token_text(TokenKindType::T_CONST)));
   }
   return m_data->replaceChild<ConstDefinitionSyntax>(constTokenRaw, Cursor::ConstToken);
}

ConstDefinitionSyntax ConstDefinitionSyntax::withDeclarations(std::optional<ConstDeclareItemListSyntax> declarations)
{
   RefCountPtr<RawSyntax> declarationsRaw;
   if (declarations.has_value()) {
      declarationsRaw = declarations->getRaw();
   } else {
      declarationsRaw = RawSyntax::missing(SyntaxKind::ConstDeclareItemList);
   }
   return m_data->replaceChild<ConstDefinitionSyntax>(declarationsRaw, Cursor::Declarations);
}

ConstDefinitionSyntax ConstDefinitionSyntax::withSemicolon(std::optional<TokenSyntax> semicolon)
{
   RefCountPtr<RawSyntax> semicolonRaw;
   if (semicolon.has_value()) {
      semicolonRaw = semicolon->getRaw();
   } else {
      semicolonRaw = RawSyntax::missing(TokenKindType::T_SEMICOLON,
                                        OwnedString::makeUnowned(get_token_text(TokenKindType::T_SEMICOLON)));
   }
   return m_data->replaceChild<ConstDefinitionSyntax>(semicolonRaw, Cursor::Semicolon);
}

///
/// TypeClauseSyntax
///

#ifdef POLAR_DEBUG_BUILD
const TokenChoicesType TypeClauseSyntax::CHILD_TOKEN_CHOICES
{
   {
      TypeClauseSyntax::Type, {
         TokenKindType::T_ARRAY,
               TokenKindType::T_CALLABLE
      }
   }
};
#endif

void TypeClauseSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == TypeClauseSyntax::CHILDREN_COUNT);
   if (const RefCountPtr<RawSyntax> &typeChild = raw->getChild(Cursor::Type)) {
      if (typeChild->isToken()) {
         syntax_assert_child_token(raw, Type, CHILD_TOKEN_CHOICES.at(Cursor::Type));
         return;
      }
      assert(typeChild->kindOf(SyntaxKind::Name));
   }
}

Syntax TypeClauseSyntax::getType()
{
   return Syntax {m_root, m_data->getChild(Cursor::Type).get()};
}

TypeClauseSyntax TypeClauseSyntax::withType(std::optional<Syntax> type)
{
   RefCountPtr<RawSyntax> typeRaw;
   if (type.has_value()) {
      typeRaw = type->getRaw();
   } else {
      typeRaw = RawSyntax::missing(SyntaxKind::Unknown);
   }
   return m_data->replaceChild<TypeClauseSyntax>(typeRaw, Cursor::Type);
}

///
/// TypeExprClauseSyntax
///
void TypeExprClauseSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == TypeExprClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, QuestionToken, std::set{TokenKindType::T_QUESTION_MARK});
   if (const RefCountPtr<RawSyntax> &typeChild = raw->getChild(Cursor::TypeClause)) {
      assert(typeChild->kindOf(SyntaxKind::TypeClause));
   }
}

std::optional<TokenSyntax> TypeExprClauseSyntax::getQuestionToken()
{
   RefCountPtr<SyntaxData> questionTokenData = m_data->getChild(Cursor::QuestionToken);
   if (!questionTokenData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, questionTokenData.get()};
}

TypeClauseSyntax TypeExprClauseSyntax::getTypeClause()
{
   return TypeClauseSyntax {m_root, m_data->getChild(Cursor::TypeClause).get()};
}

TypeExprClauseSyntax TypeExprClauseSyntax::withQuestionToken(std::optional<TokenSyntax> questionToken)
{
   RefCountPtr<RawSyntax> questionTokenRaw;
   if (questionToken.has_value()) {
      questionTokenRaw = questionToken->getRaw();
   } else {
      questionTokenRaw = nullptr;
   }
   return m_data->replaceChild<TypeExprClauseSyntax>(questionTokenRaw, Cursor::QuestionToken);
}

TypeExprClauseSyntax TypeExprClauseSyntax::withType(std::optional<TypeClauseSyntax> type)
{
   RefCountPtr<RawSyntax> typeRaw;
   if (type.has_value()) {
      typeRaw = type->getRaw();
   } else {
      typeRaw = nullptr;
   }
   return m_data->replaceChild<TypeExprClauseSyntax>(typeRaw, Cursor::TypeClause);
}

///
/// ReturnTypeClauseSyntax
///
void ReturnTypeClauseSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == ReturnTypeClauseSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, ColonToken, std::set{TokenKindType::T_COLON});
   if (const RefCountPtr<RawSyntax> &typeExprChild = raw->getChild(Cursor::TypeExpr)) {
      assert(typeExprChild->kindOf(SyntaxKind::TypeExprClause));
   }
}

TokenSyntax ReturnTypeClauseSyntax::getColon()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::ColonToken).get()};
}

TypeExprClauseSyntax ReturnTypeClauseSyntax::getType()
{
   return TypeExprClauseSyntax {m_root, m_data->getChild(Cursor::TypeExpr).get()};
}

ReturnTypeClauseSyntax ReturnTypeClauseSyntax::withColon(std::optional<TokenSyntax> colon)
{
   RefCountPtr<RawSyntax> colonRaw;
   if (colon.has_value()) {
      colonRaw = colon->getRaw();
   } else {
      colonRaw = RawSyntax::missing(TokenKindType::T_COLON,
                                    OwnedString::makeUnowned(get_token_text(TokenKindType::T_COLON)));
   }
   return m_data->replaceChild<ReturnTypeClauseSyntax>(colonRaw, Cursor::ColonToken);
}

ReturnTypeClauseSyntax ReturnTypeClauseSyntax::withType(std::optional<TypeExprClauseSyntax> type)
{
   RefCountPtr<RawSyntax> typeRaw;
   if (type.has_value()) {
      typeRaw = type->getRaw();
   } else {
      typeRaw = RawSyntax::missing(SyntaxKind::TypeExprClause);
   }
   return m_data->replaceChild<ReturnTypeClauseSyntax>(typeRaw, Cursor::TypeExpr);
}

///
/// ParameterSyntax
///
void ParameterSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == ParameterSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, ReferenceMark, std::set{TokenKindType::T_AMPERSAND});
   syntax_assert_child_token(raw, VariadicMark, std::set{TokenKindType::T_ELLIPSIS});
   syntax_assert_child_token(raw, Variable, std::set{TokenKindType::T_VARIABLE});
   if (const RefCountPtr<RawSyntax> &typeHintChild = raw->getChild(Cursor::TypeHint)) {
      assert(typeHintChild->kindOf(SyntaxKind::TypeExprClause));
   }
   if (const RefCountPtr<RawSyntax> &initializerChild = raw->getChild(Cursor::Initializer)) {
      assert(initializerChild->kindOf(SyntaxKind::InitializeClause));
   }
}

std::optional<TypeExprClauseSyntax> ParameterSyntax::getTypeHint()
{
   RefCountPtr<SyntaxData> typeHintData = m_data->getChild(Cursor::TypeHint);
   if (!typeHintData) {
      return std::nullopt;
   }
   return TypeExprClauseSyntax {m_root, typeHintData.get()};
}

std::optional<TokenSyntax> ParameterSyntax::getReferenceMark()
{
   RefCountPtr<SyntaxData> referenceData = m_data->getChild(Cursor::ReferenceMark);
   if (!referenceData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, referenceData.get()};
}

std::optional<TokenSyntax> ParameterSyntax::getVariadicMark()
{
   RefCountPtr<SyntaxData> variadicData = m_data->getChild(Cursor::VariadicMark);
   if (!variadicData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, variadicData.get()};
}

TokenSyntax ParameterSyntax::getVariable()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Variable).get()};
}

std::optional<InitializeClauseSyntax> ParameterSyntax::getInitializer()
{
    RefCountPtr<SyntaxData> initializerData = m_data->getChild(Cursor::Initializer);
    if (!initializerData) {
       return std::nullopt;
    }
    return InitializeClauseSyntax {m_root, initializerData.get()};
}

ParameterSyntax ParameterSyntax::withTypeHint(std::optional<TypeExprClauseSyntax> typeHint)
{
   RefCountPtr<RawSyntax> typeHintRaw;
   if (typeHint.has_value()) {
      typeHintRaw = typeHint->getRaw();
   } else {
      typeHintRaw = nullptr;
   }
   return m_data->replaceChild<ParameterSyntax>(typeHintRaw, Cursor::TypeHint);
}

ParameterSyntax ParameterSyntax::withReferenceMark(std::optional<TokenSyntax> referenceMark)
{
   RefCountPtr<RawSyntax> referenceMarkRaw;
   if (referenceMark.has_value()) {
      referenceMarkRaw = referenceMark->getRaw();
   } else {
      referenceMarkRaw = nullptr;
   }
   return m_data->replaceChild<ParameterSyntax>(referenceMarkRaw, Cursor::ReferenceMark);
}

ParameterSyntax ParameterSyntax::withVariadicMark(std::optional<TokenSyntax> variadicMark)
{
   RefCountPtr<RawSyntax> variadicMarkRaw;
   if (variadicMark.has_value()) {
      variadicMarkRaw = variadicMark->getRaw();
   } else {
      variadicMarkRaw = nullptr;
   }
   return m_data->replaceChild<ParameterSyntax>(variadicMarkRaw, Cursor::VariadicMark);
}

ParameterSyntax ParameterSyntax::withVariable(std::optional<TokenSyntax> variable)
{
   RefCountPtr<RawSyntax> variableRaw;
   if (variable.has_value()) {
      variableRaw = variable->getRaw();
   } else {
      variableRaw = RawSyntax::missing(TokenKindType::T_VARIABLE,
                                       OwnedString::makeUnowned(get_token_text(TokenKindType::T_VARIABLE)));
   }
   return m_data->replaceChild<ParameterSyntax>(variableRaw, Cursor::Variable);
}

ParameterSyntax ParameterSyntax::withInitializer(std::optional<InitializeClauseSyntax> initializer)
{
   RefCountPtr<RawSyntax> initializerRaw;
   if (initializer.has_value()) {
      initializerRaw = initializer->getRaw();
   } else {
      initializerRaw = RawSyntax::missing(SyntaxKind::InitializeClause);
   }
   return m_data->replaceChild<ParameterSyntax>(initializerRaw, Cursor::Initializer);
}

///
/// LexicalVarItemSyntax
///
void LexicalVarItemSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().getSize() == LexicalVarItemSyntax::CHILDREN_COUNT);
   syntax_assert_child_token(raw, ReferenceToken, std::set{TokenKindType::T_AMPERSAND});
   syntax_assert_child_token(raw, Variable, std::set{TokenKindType::T_VARIABLE});
}

std::optional<TokenSyntax> LexicalVarItemSyntax::getReferenceToken()
{
   RefCountPtr<SyntaxData> refData = m_data->getChild(Cursor::ReferenceToken);
   if (!refData) {
      return std::nullopt;
   }
   return TokenSyntax {m_root, refData.get()};
}

TokenSyntax LexicalVarItemSyntax::getVariable()
{
   return TokenSyntax {m_root, m_data->getChild(Cursor::Variable).get()};
}

LexicalVarItemSyntax LexicalVarItemSyntax::withReferenceToken(std::optional<TokenSyntax> referenceToken)
{
   RefCountPtr<RawSyntax> referenceTokenRaw;
   if (referenceToken.has_value()) {
      referenceTokenRaw = referenceToken->getRaw();
   } else {
      referenceTokenRaw = nullptr;
   }
   return m_data->replaceChild<LexicalVarItemSyntax>(referenceTokenRaw, Cursor::ReferenceToken);
}

LexicalVarItemSyntax LexicalVarItemSyntax::withVariable(std::optional<TokenSyntax> variable)
{
   RefCountPtr<RawSyntax> variableRaw;
   if (variable.has_value()) {
      variableRaw = variable->getRaw();
   } else {
      variableRaw = RawSyntax::missing(TokenKindType::T_VARIABLE,
                                       OwnedString::makeUnowned(get_token_text(TokenKindType::T_VARIABLE)));
   }
   return m_data->replaceChild<LexicalVarItemSyntax>(variableRaw, Cursor::Variable);
}

///
/// SourceFileSyntax
///
void SourceFileSyntax::validate()
{
   RefCountPtr<RawSyntax> raw = m_data->getRaw();
   if (isMissing()) {
      return;
   }
   assert(raw->getLayout().size() == SourceFileSyntax::CHILDREN_COUNT);
}

TokenSyntax SourceFileSyntax::getEofToken()
{
   return TokenSyntax{m_root, m_data->getChild(Cursor::EOFToken).get()};
}

CodeBlockItemListSyntax SourceFileSyntax::getStatements()
{
   return CodeBlockItemListSyntax{m_root, m_data->getChild(Cursor::Statements).get()};
}

SourceFileSyntax SourceFileSyntax::withStatements(std::optional<CodeBlockItemListSyntax> statements)
{
   RefCountPtr<RawSyntax> rawStatements;
   if (statements.has_value()) {
      rawStatements = statements->getRaw();
   } else {
      rawStatements = RawSyntax::missing(SyntaxKind::CodeBlockItemList);
   }
   return m_data->replaceChild<SourceFileSyntax>(rawStatements, Cursor::Statements);
}

SourceFileSyntax SourceFileSyntax::addStatement(CodeBlockItemSyntax statement)
{
   RefCountPtr<RawSyntax> rawStatements = getRaw()->getChild(Cursor::Statements);
   if (rawStatements) {
      rawStatements->append(statement.getRaw());
   } else {
      rawStatements = RawSyntax::make(SyntaxKind::CodeBlockItemList, {statement.getRaw()}, SourcePresence::Present);
   }
   return m_data->replaceChild<SourceFileSyntax>(rawStatements, Cursor::Statements);
}

SourceFileSyntax SourceFileSyntax::withEofToken(std::optional<TokenSyntax> eofToken)
{
   RefCountPtr<RawSyntax> rawEofToken;
   if (eofToken.has_value()) {
      rawEofToken = eofToken->getRaw();
   } else {
      rawEofToken = RawSyntax::missing(TokenKindType::END, OwnedString::makeUnowned(""));
   }
   return m_data->replaceChild<SourceFileSyntax>(rawEofToken, Cursor::EOFToken);
}

} // polar::syntax
