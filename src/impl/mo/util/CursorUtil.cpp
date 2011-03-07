#include <clang/AST/Stmt.h>
#include <clang/AST/Decl.h>

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
