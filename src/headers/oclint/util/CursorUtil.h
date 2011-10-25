#ifndef OCLINT_UTIL_CURSORUTIL_H
#define OCLINT_UTIL_CURSORUTIL_H

#include <clang-c/Index.h>

namespace clang {
  class Decl;
  class Stmt;
  class Expr;
  class ASTContext;
}

using namespace clang;

class CursorUtil {
public:
  static Decl* getDecl(CXCursor node);
  static Stmt* getStmt(CXCursor node);
  static Expr* getExpr(CXCursor node);
  static ASTContext& getASTContext(CXCursor node);
  static bool isCursorDeclaredInCurrentFile(CXCursor node);
};

#endif
