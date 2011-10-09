#include "mo/rule/ConstantIfStatementRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/Expr.h>
#include <clang/AST/Decl.h>

using namespace clang;

RuleSet ConstantIfStatementRule::rules(new ConstantIfStatementRule());

void ConstantIfStatementRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorUtil::getStmt(node);
  if (stmt) {
    IfStmt *ifStmt = dyn_cast<IfStmt>(stmt);
    if (ifStmt) {
      Expr *conditionExpression = ifStmt->getCond();
      
      bool evaluatedResult;
      if (conditionExpression->EvaluateAsBooleanCondition(evaluatedResult, CursorUtil::getASTContext(node))) {
        Violation violation(node, this);
        violationSet.addViolation(violation);
      }
    }
  }
}

const string ConstantIfStatementRule::name() const {
  return "constant if statement";
}
