#ifndef OCLINT_RULE_REDUNDANTIFSTATEMENTRULE_H
#define OCLINT_RULE_REDUNDANTIFSTATEMENTRULE_H

#include "oclint/Rule.h"

namespace clang
{
  class Stmt;
  class ReturnStmt;
  class Expr;
  class BinaryOperator;
}

using namespace clang;

class RedundantIfStatementRule : public Rule
{
private:
  static RuleSet rules;

  template<typename nodeType>
  nodeType* extractStmt(Stmt *fromStmt);

  bool isCIntegerViolated(Expr *thenExpr, Expr *elseExpr);
  bool isCXXBoolViolated(Expr *thenExpr, Expr *elseExpr);
  bool isObjCBOOLViolated(Expr *thenExpr, Expr *elseExpr);

  bool isNotEquals(Expr *firstExpr, Expr *secondExpr);
  bool doesReturnStatementsViolateRule(ReturnStmt *first, ReturnStmt *second);
  bool doesBinaryOperatorsViolateRule(
    BinaryOperator *first, BinaryOperator *second);

public:
  virtual void apply(
    CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
