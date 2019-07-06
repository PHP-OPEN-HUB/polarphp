// This source file is part of the polarphp.org open source project
//
// Copyright (c) 2017 - 2019 polarphp software foundation
// Copyright (c) 2017 - 2019 zzu_softboy <zzu_softboy@163.com>
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://polarphp.org/LICENSE.txt for license information
// See https://polarphp.org/CONTRIBUTORS.txt for the list of polarphp project authors
//
// Created by polarboy on 2019/05/07.

//===----------------------------------------------------------------------===//
//
//  This file defines the Token interface.
//
//===----------------------------------------------------------------------===//

#ifndef POLAR_PARSER_TOKEN_H
#define POLAR_PARSER_TOKEN_H

#include "polarphp/basic/adt/StringRef.h"
#include "polarphp/utils/SourceLocation.h"
#include "polarphp/parser/SourceLoc.h"
#include "polarphp/syntax/TokenKinds.h"
#include "polarphp/parser/internal/YYParserDefs.h"

#include <any>

/// forward declare class with namespace
namespace polar::utils {
class RawOutStream;
}

namespace polar::parser {

using polar::basic::StringRef;
using polar::utils::RawOutStream;
using polar::syntax::TokenKindType;
using polar::parser::internal::ParserSemantic;

/// Token - This structure provides full information about a lexed token.
/// It is not intended to be space efficient, it is intended to return as much
/// information as possible about each returned token.  This is expected to be
/// compressed into a smaller form if memory footprint is important.
///
class Token
{
public:
   enum class ValueType
   {
      Unknown,
      LongLong,
      String,
      Double
   };

   Token(TokenKindType kind, StringRef text, unsigned commentLength = 0)
      : m_atStartOfLine(false),
        m_escapedIdentifier(false),
        m_kind(kind),
        m_commentLength(commentLength),
        m_valueType(ValueType::Unknown),
        m_text(text)
   {}

   Token()
      : Token(TokenKindType::T_UNKOWN_MARK, {}, 0)
   {}

   TokenKindType getKind() const
   {
      return m_kind;
   }

   void setKind(TokenKindType kind)
   {
      m_kind = kind;
   }

   void clearCommentLegth()
   {
      m_commentLength = 0;
   }

   bool is(TokenKindType kind) const
   {
      return m_kind == kind;
   }

   bool isNot(TokenKindType kind) const
   {
      return m_kind != kind;
   }

   // Predicates to check to see if the token is any of a list of tokens.
   bool isAny(TokenKindType kind) const
   {
      return is(kind);
   }

   template <typename ...T>
   bool isAny(TokenKindType token1, TokenKindType token2, T... tokens) const
   {
      if (is(token1)) {
         return true;
      }
      return isAny(token2, tokens...);
   }

   template <typename ...T>
   bool isNot(TokenKindType token1, T... tokens) const
   {
      return isAny(token1, tokens...);
   }

   bool isBinaryOperator() const
   {
   }

   bool isAnyOperator() const
   {
   }

   bool isNotAnyOperator() const
   {
      return !isAnyOperator();
   }

   /// Determine whether this token occurred at the start of a line.
   bool isAtStartOfLine() const
   {
      return m_atStartOfLine;
   }

   /// Set whether this token occurred at the start of a line.
   void setAtStartOfLine(bool value)
   {
      m_atStartOfLine = value;
   }

   /// True if this token is an escaped identifier token.
   bool isEscapedIdentifier() const
   {
      return m_escapedIdentifier;
   }

   /// Set whether this token is an escaped identifier token.
   void setEscapedIdentifier(bool value)
   {
   }

   /// True if the token is an identifier
   bool isIdentifier() const
   {
      return false;
   }

   /// True if the token is any keyword.
   bool isKeyword() const
   {
      return false;
   }

   /// True if the token is any literal.
   bool isLiteral() const
   {
      return false;
   }

   bool isPunctuation() const
   {
      return false;
   }

   bool hasValue() const
   {
      return m_value.has_value();
   }

   /// getLoc - Return a source location identifier for the specified
   /// offset in the current file.
   SourceLoc getLoc() const
   {
      return SourceLoc(polar::utils::SMLocation::getFromPointer(m_text.begin()));
   }

   unsigned getLength() const
   {
      return m_text.size();
   }

   CharSourceRange getRange() const
   {
      return CharSourceRange(getLoc(), getLength());
   }

   CharSourceRange getRangeWithoutBackticks() const
   {
      SourceLoc TokLoc = getLoc();
      unsigned TokLength = getLength();
      if (isEscapedIdentifier()) {
         // Adjust to account for the backticks.
         TokLoc = TokLoc.getAdvancedLoc(1);
         TokLength -= 2;
      }
      return CharSourceRange(TokLoc, TokLength);
   }

   bool hasComment() const
   {
      return m_commentLength != 0;
   }

   CharSourceRange getCommentRange() const
   {
      if (m_commentLength == 0) {
         return CharSourceRange(SourceLoc(polar::utils::SMLocation::getFromPointer(m_text.begin())),
                                0);
      }

      auto trimedComment = trimComment();
      return CharSourceRange(
               SourceLoc(polar::utils::SMLocation::getFromPointer(trimedComment.begin())),
               trimedComment.size());
   }

   SourceLoc getCommentStart() const
   {
      if (m_commentLength == 0) {
         return SourceLoc();
      }
      return SourceLoc(polar::utils::SMLocation::getFromPointer(trimComment().begin()));
   }

   StringRef getRawText() const
   {
      return m_text;
   }

   StringRef getText() const
   {
      if (m_escapedIdentifier) {
         // Strip off the backticks on either side.
         assert(m_text.front() == '`' && m_text.back() == '`');
         return m_text.slice(1, m_text.size() - 1);
      }
      return m_text;
   }

   Token &setText(StringRef text)
   {
      m_text = text;
      return *this;
   }

   Token &setValue(StringRef value)
   {
      m_valueType = ValueType::String;
      m_value.emplace<std::string>(value.data(), value.getSize());
      return *this;
   }

   Token &setValue(std::int64_t value)
   {
      m_valueType = ValueType::LongLong;
      m_value.emplace<std::int64_t>(value);
      return *this;
   }

   Token &setValue(double value)
   {
      m_valueType = ValueType::Double;
      m_value.emplace<double>(value);
      return *this;
   }

   template <typename T,
             typename std::enable_if_t<std::disjunction_v<std::is_same_v<T, std::string>,
                                                          std::is_same_v<T, double>,
                                                          std::is_same_v<T, std::int64_t>>>>
   const T &getValue()
   {
      assert(m_value.has_value());
      return std::any_cast<const T &>(m_value);
   }

   ValueType getValueType() const
   {
      return m_valueType;
   }

   Token &setValueType(ValueType type)
   {
      m_valueType = type;
      m_value.reset();
      return *this;
   }

   Token &resetValueType()
   {
      m_valueType = ValueType::Unknown;
      m_value.reset();
      return *this;
   }

   /// Set the token to the specified kind and source range.
   Token &setToken(TokenKindType kind, StringRef text = StringRef(), unsigned commentLength = 0)
   {
      m_kind = kind;
      m_text = text;
      m_commentLength = commentLength;
      m_escapedIdentifier = false;
      return *this;
   }
private:
   StringRef trimComment() const
   {
      assert(hasComment() && "Has no comment to trim.");
      StringRef raw(m_text.begin() - m_commentLength, m_commentLength);
      return raw.trim();
   }

private:
   /// Whether this token is the first token on the line.
   unsigned m_atStartOfLine : 1;

   /// Whether this token is an escaped `identifier` token.
   unsigned m_escapedIdentifier : 1;

   /// Kind - The actual flavor of token this is.
   TokenKindType m_kind;

   /// The length of the comment that precedes the token.
   unsigned int m_commentLength;

   ValueType m_valueType;

   /// Text - The actual string covered by the token in the source buffer.
   StringRef m_text;

   /// The token value
   std::any m_value;
};

} // polar::syntax

#endif // POLAR_PARSER_TOKEN_H
