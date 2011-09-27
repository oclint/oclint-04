#ifndef LLVM_CLANG_CXTRANSLATIONUNIT_H
#define LLVM_CLANG_CXTRANSLATIONUNIT_H

extern "C" {
struct CXTranslationUnitImpl {
  void *TUData;
  void *StringPool;
};
}

#endif

#include <clang/AST/Stmt.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/AST/ASTContext.h>
#include <clang/Frontend/ASTUnit.h>

#include "mo/util/CursorUtil.h"

Decl* CursorUtil::getDecl(CXCursor node) {
  if (clang_isDeclaration(clang_getCursorKind(node))) {
    return (Decl *)node.data[0];
  }
  return NULL;
}

Stmt* CursorUtil::getStmt(CXCursor node) {
  if (clang_isStatement(clang_getCursorKind(node))) {
    return (Stmt *)node.data[1];
  }
  return NULL;
}

Expr* CursorUtil::getExpr(CXCursor node) {
  if (clang_isExpression(clang_getCursorKind(node))) {
    return (Expr *)node.data[1];
  }
  return NULL;
}

ASTContext& CursorUtil::getASTContext(CXCursor node) {
  CXTranslationUnit translationUnit = (CXTranslationUnit)node.data[2];
  ASTUnit *astUnit = (ASTUnit *)translationUnit->TUData;
  return astUnit->getASTContext();
}
