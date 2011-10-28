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

#include "oclint/util/CursorUtil.h"

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

string CursorUtil::itoa(int i) {
  if (i == 0) {
    return "0";
  }
  string intermediateString = "";
  while (i > 0) {
    intermediateString += i % 10 + 48;
    i /= 10;
  }
  string returnString = "";
  for (int index = 0; index < intermediateString.length(); index++) {
    returnString += intermediateString[intermediateString.length() - index - 1];
  }
  return returnString;
}

string CursorUtil::getFileName(CXCursor cursor) {
  CXFile file;
  clang_getSpellingLocation(clang_getCursorLocation(cursor), &file, 0, 0, 0);
  CXString fileStr = clang_getFileName(file);
  string fileName(clang_getCString(fileStr));
  clang_disposeString(fileStr);
  return fileName;
}

string CursorUtil::getLineNumber(CXCursor cursor) {
  unsigned line;
  clang_getSpellingLocation(clang_getCursorLocation(cursor), 0, &line, 0, 0);
  return itoa(line);
}

string CursorUtil::getColumnNumber(CXCursor cursor) {
  unsigned column;
  clang_getSpellingLocation(clang_getCursorLocation(cursor), 0, 0, &column, 0);
  return itoa(column);
}
