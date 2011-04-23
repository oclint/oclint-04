#ifndef MO_UTIL_CURSORUTIL_H
#define MO_UTIL_CURSORUTIL_H

#include <clang-c/Index.h>

namespace clang {
  class Decl;
  class Stmt;
  class Expr;
}

using namespace clang;

class CursorUtil {
public:
  static Decl* getDecl(CXCursor node);
  static Stmt* getStmt(CXCursor node);
  static Expr* getExpr(CXCursor node);
};

#endif
