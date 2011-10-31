#ifndef OCLINT_HELPER_CYCLOMATICCOMPLEXITYMEASUREMENT_H
#define OCLINT_HELPER_CYCLOMATICCOMPLEXITYMEASUREMENT_H

#include <clang-c/Index.h>

namespace clang {
  class Stmt;
  class Expr;
}

class CyclomaticComplexityMeasurement {
private:
  static bool isDecisionPoint(clang::Stmt *stmt);
  static bool isDecisionPoint(clang::Expr *expr);
  
public:
  static int getCCNOfCursor(CXCursor node);
};

#endif
