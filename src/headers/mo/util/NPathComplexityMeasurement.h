#ifndef MO_UTIL_NPATHCOMPLEXITYMEASUREMENT_H
#define MO_UTIL_NPATHCOMPLEXITYMEASUREMENT_H

#include <clang-c/Index.h>

namespace clang {
  class Stmt;
  class CompoundStmt;
  class IfStmt;
  
  class Expr;
  class ConditionalOperator;
  class BinaryOperator;
}

using namespace clang;

class NPathComplexityMeasurement {
private:
  static int nPath(Stmt *stmt);
  static int nPath(CompoundStmt *stmt);
  static int nPath(IfStmt *stmt);
  
  static int nPath(Expr *expr);
  static int nPath(ConditionalOperator *expr);
  static int nPath(BinaryOperator *expr);
  
public:
  static int getNPathOfCursor(CXCursor node);
};

#endif
