// This source file is part of the polarphp.org open source project
//
// Copyright (c) 2017 - 2019 polarphp software foundation
// Copyright (c) 2017 - 2019 zzu_softboy <zzu_softboy@163.com>
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://polarphp.org/LICENSE.txt for license information
// See https://polarphp.org/CONTRIBUTORS.txt for the list of polarphp project authors
//
// Created by polarboy on 2019/05/11.

#ifndef POLARPHP_SYNTAX_KIND_ENUM_DEFS_H
#define POLARPHP_SYNTAX_KIND_ENUM_DEFS_H

#include <cstdint>

namespace polar::syntax {

enum class SyntaxKind : std::uint32_t
{
   Token,

   /// common syntax node
   Decl,
   Expr,
   Stmt,
   Type,

   /// decl syntax node
   FirstDecl,
   ReservedNonModifier,
   SemiReserved,
   Identifier,
   NamespaceName,
   TypeClause,
   TypeExprClause,
   Name,
   NameListItem,
   ReturnTypeClause,
   InitializerClause, // for variable assign or initialize
   Parameter,
   ParameterListItem,
   ParameterListClause,
   LexicalVariable,
   LexicalVariableListItem,
   UseLexicalVarClause,
   FunctionDefinition,
   /// for class definition
   ClassModifier,
   ImplementsClause,
   InterfaceExtendsClause,
   ExtendsFromClause,
   ClassPropertyClause,
   ClassPropertyListItem,
   ClassConstClause,
   ClassConstListItem,
   ClassPropertyDecl,
   ClassConstDecl,
   ClassMethodDecl,
   /// class traint use clauses
   ClassTraitMethodReference,
   ClassAbsoluteTraitMethodReference,
   ClassTraitPrecedence,
   ClassTraitAlias,
   ClassTraitAdaptation,
   ClassTraitAdaptationBlock,
   ClassTraitDecl,
   MemberModifier,
   MemberDeclBlock,
   MemberDeclListItem,
   ClassDefinition,
   InterfaceDefinition,
   TraitDefinition,

   UnknownDecl,
   LastDecl,

   /// expr syntax node
   FirstExpr,
   ParenDecoratedExpr,
   NullExpr,
   OptionalExpr,
   ExprListItem,

   VariableExpr,
   ReferencedVariableExpr,
   ClassConstIdentifierExpr,
   ConstExpr,
   StaticMemberExpr,
   NewVariableClause,
   CallableVariableExpr,
   CallableFuncNameClause,
   MemberNameClause,
   PropertyNameClause,
   InstancePropertyExpr,
   StaticPropertyExpr,

   // argument clauses
   Argument,
   ArgumentListItem,
   ArgumentListClause,

   DereferencableClause,
   VariableClassNameClause,
   ClassNameClause,
   ClassNameRefClause,

   BraceDecoratedExprClause,
   BraceDecoratedVariableExpr,
   ArrayKeyValuePairItem,
   ArrayUnpackPairItem,
   ArrayPair,
   ArrayPairListItem,
   ListRecursivePairItem,
   ListPairItem,
   SimpleVariableExpr,
   ArrayCreateExpr,
   SimplifiedArrayCreateExpr,
   ArrayAccessExpr,
   BraceDecoratedArrayAccessExpr,
   SimpleFunctionCallExpr,
   FunctionCallExpr,
   InstanceMethodCallExpr,
   StaticMethodCallExpr,
   FloatLiteralExpr,
   IntegerLiteralExpr,
   StringLiteralExpr,

   // function like lang structure
   IssetVariable,
   IssetVariableListItem,
   IssetVariablesClause,
   IssetFuncExpr,
   EmptyFuncExpr,
   IncludeExpr,
   RequireExpr,
   EvalFuncExpr,
   PrintFuncExpr,
   FuncLikeExpr,

   ArrayStructureAssignmentExpr,
   ListStructureClause,
   ListStructureAssignmentExpr,
   AssignmentExpr,
   CompoundAssignmentExpr,
   BitLogicalExpr,
   LogicalExpr,
   RelationExpr,
   CastExpr,
   ExitExprArgClause,
   ExitExpr,
   YieldExpr,
   YieldFromExpr,
   CloneExpr,

   EncapsVariableOffset,
   EncapsArrayVar,
   EncapsObjProp,
   EncapsDollarCurlyExpr,
   EncapsDollarCurlyVar,
   EncapsDollarCurlyArray,
   EncapsCurlyVariable,
   EncapsVariable,
   EncapsListItem,
   BackticksClause,

   HeredocExpr,
   EncapsListStringExpr,
   DereferencableScalarExpr,
   AnonymousClassDefinitionClause,
   SimpleInstanceCreateExpr,
   AnonymousInstanceCreateExpr,
   ClassicLambdaExpr,
   SimplifiedLambdaExpr,
   LambdaExpr,
   InstanceCreateExpr,
   ScalarExpr,
   BooleanLiteralExpr,
   TernaryExpr,
   SequenceExpr,
   ClassRefParentExpr,
   ClassRefStaticExpr,
   ClassRefSelfExpr,
   PrefixOperatorExpr,
   PostfixOperatorExpr,
   BinaryOperatorExpr,
   InstanceofExpr,
   ShellCmdExpr,
   UnknownExpr,
   LastExpr,

   /// decl syntax node
   SourceFile,

   /// stmt syntax node
   FirstStmt,
   ExprStmt,
   NestStmt,
   EmptyStmt,
   ConditionElement,
   InnerStmt,
   InnerCodeBlockStmt,
   TopStmt,
   TopCodeBlockStmt,
   DeclareStmt,
   GotoStmt,
   UnsetVariable,
   UnsetVariableListItem,
   UnsetStmt,
   LabelStmt,
   ContinueStmt,
   BreakStmt,
   FallthroughStmt,
   WhileStmt,
   DoWhileStmt,
   ForStmt,
   ForeachVariable,
   ForeachStmt,
   SwitchCase,
   SwitchDefaultLabel,
   SwitchCaseLabel,
   SwitchCaseListClause,
   SwitchStmt,
   ElseIfClause,
   IfStmt,
   DeferStmt,
   ExpressionStmt,
   ThrowStmt,
   TryStmt,
   FinallyClause,
   CatchArgTypeHintItem,
   CatchListItemClause,
   ReturnStmt,
   EchoStmt,
   HaltCompilerStmt,
   GlobalVariable,
   GlobalVariableListItem,
   GlobalVariableDeclarationsStmt,
   StaticVariableDeclare,
   StaticVariableListItem,
   StaticVariableDeclarationsStmt,

   NamespaceUseType,
   NamespaceUnprefixedUseDeclaration,
   NamespaceUnprefixedUseDeclarationListItem,
   NamespaceUseDeclaration,
   NamespaceUseDeclarationListItem,
   NamespaceInlineUseDeclaration,
   NamespaceInlineUseDeclarationListItem,
   NamespaceGroupUseDeclaration,
   NamespaceMixedGroupUseDeclaration,
   NamespaceUseStmt,
   NamespaceDefinitionStmt,
   NamespaceBlockStmt,

   ConstDeclare,
   ConstListItem,
   ConstDefinitionStmt,

   ClassDefinitionStmt,
   InterfaceDefinitionStmt,
   TraitDefinitionStmt,
   FunctionDefinitionStmt,
   UnknownStmt,
   LastStmt,

   /// collection syntax node
   ConditionElementList,
   SwitchCaseList,
   ElseIfList,
   CodeBlockItemList,
   InnerStmtList,
   TopStmtList,
   ExprList,
   EchoExprList,
   NameList,
   NamespaceUseDeclarationList,
   NamespaceInlineUseDeclarationList,
   NamespaceUnprefixedUseDeclarationList,
   ConstDeclareList,
   ParameterList,
   LexicalVarList,
   ClassPropertyList,
   ClassConstList,
   ClassModifierList,
   ClassTraitAdaptationList,
   /// for array
   ArrayPairList,
   MemberModifierList,
   MemberDeclList,
   EncapsList,
   ArgumentList,
   IssetVariablesList,
   CatchList,
   CatchArgTypeHintList,
   UnsetVariableList,
   GlobalVariableList,
   StaticVariableList,
   // NOTE: Unknown must be the last kind.
   Unknown,
};

} // polar::syntax

#endif // POLARPHP_SYNTAX_KIND_ENUM_DEFS_H
