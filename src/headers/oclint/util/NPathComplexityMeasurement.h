#ifndef OCLINT_UTIL_NPATHCOMPLEXITYMEASUREMENT_H
#define OCLINT_UTIL_NPATHCOMPLEXITYMEASUREMENT_H

#include <clang-c/Index.h>

namespace clang {
  class Stmt;
  class CompoundStmt;
  class IfStmt;
  class WhileStmt;
  class DoStmt;
  class ForStmt;
  class SwitchStmt;
  class ObjCForCollectionStmt;
  
  class Expr;
  class ConditionalOperator;
  class BinaryOperator;
  class ParenExpr;
}

using namespace clang;

class NPathComplexityMeasurement {
private:
  static int nPath(Stmt *node);
  static int nPath(CompoundStmt *stmt);
  static int nPath(IfStmt *stmt);
  static int nPath(WhileStmt *stmt);
  static int nPath(DoStmt *stmt);
  static int nPath(ForStmt *stmt);
  static int nPath(SwitchStmt *stmt);
  static int nPath(ObjCForCollectionStmt *stmt);
  
  static int nPath(Expr *node);
  static int nPath(ConditionalOperator *expr);
  static int nPath(BinaryOperator *expr);
  static int nPath(ParenExpr *expr);
  
public:
  static int getNPathOfCursor(CXCursor cursor);

private:
  static CompoundStmt* extractCompoundStmtFromCursor(CXCursor cursor);
  static CompoundStmt* extractCompoundStmtFromMethodDeclCursor(CXCursor cursor);
};

#endif
