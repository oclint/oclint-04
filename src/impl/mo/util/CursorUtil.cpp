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
#include <clang/Basic/SourceManager.h>
#include <clang/Basic/SourceLocation.h>

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
  ASTUnit *astUnit = static_cast<ASTUnit *>(static_cast<CXTranslationUnit>(node.data[2])->TUData);
  return astUnit->getASTContext();
}

bool CursorUtil::isCursorDeclaredInCurrentFile(CXCursor node) {
  FileID fileId;
  Decl *decl = CursorUtil::getDecl(node);
  Stmt *stmt = CursorUtil::getStmt(node);
  if (decl) {
    fileId = CursorUtil::getASTContext(node).getSourceManager().getFileID(decl->getLocation());
  }
  else if (stmt) {
    fileId = CursorUtil::getASTContext(node).getSourceManager().getFileID(stmt->getLocStart());
  }
  else {
    return false;
  }
  SourceLocation sourceLocation = CursorUtil::getASTContext(node).getSourceManager().getIncludeLoc(fileId);
  return sourceLocation.isInvalid();
}
