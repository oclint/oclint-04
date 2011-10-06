#ifndef MO_RULE_REDUNDANTIFSTATEMENTRULE_H
#define MO_RULE_REDUNDANTIFSTATEMENTRULE_H

#include "mo/Rule.h"

namespace clang {
  class Stmt;
  class ReturnStmt;
  class Expr;
}

using namespace clang;

class RedundantIfStatementRule : public Rule {
private:
  static RuleSet rules;
  
  ReturnStmt* extractReturnStmt(Stmt *fromStmt);
  bool isCIntegerViolated(Expr *thenExpr, Expr *elseExpr);
  bool isCXXBoolViolated(Expr *thenExpr, Expr *elseExpr);
  bool isObjCBOOLViolated(Expr *thenExpr, Expr *elseExpr);
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
