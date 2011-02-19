#ifndef MO_UTIL_RULEUTIL_H
#define MO_UTIL_RULEUTIL_H

#include <clang-c/Index.h>

namespace clang {
  class Decl;
  class Stmt;
}

using namespace clang;

class RuleUtil {
public:
  static Decl* getCursorDecl(CXCursor node);
  static Stmt* getCursorStmt(CXCursor node);
};

#endif
