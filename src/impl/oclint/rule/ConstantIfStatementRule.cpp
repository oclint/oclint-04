#include "oclint/rule/ConstantIfStatementRule.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/Expr.h>
#include <clang/AST/Decl.h>

#include "oclint/RuleSet.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/helper/CursorHelper.h"

using namespace clang;

RuleSet ConstantIfStatementRule::rules(new ConstantIfStatementRule());

void ConstantIfStatementRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorHelper::getStmt(node);
  if (stmt) {
    IfStmt *ifStmt = dyn_cast<IfStmt>(stmt);
    if (ifStmt) {
      Expr *conditionExpression = ifStmt->getCond();
      
      bool evaluatedResult;
      if (conditionExpression->EvaluateAsBooleanCondition(evaluatedResult, CursorHelper::getASTContext(node))) {
        Violation violation(node, this);
        violationSet.addViolation(violation);
      }
    }
  }
}

const string ConstantIfStatementRule::name() const {
  return "constant if statement";
}
