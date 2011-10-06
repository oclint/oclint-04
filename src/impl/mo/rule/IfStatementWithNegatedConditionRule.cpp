#include "mo/rule/IfStatementWithNegatedConditionRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/Expr.h>

using namespace clang;

RuleSet IfStatementWithNegatedConditionRule::rules(new IfStatementWithNegatedConditionRule());

void IfStatementWithNegatedConditionRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorUtil::getStmt(node);
  if (stmt) {
    IfStmt *ifStmt = dyn_cast<IfStmt>(stmt);
    if (ifStmt) {
      Stmt *elseBlock = ifStmt->getElse();
      if (elseBlock) {
        UnaryOperator *unaryOperator = dyn_cast<UnaryOperator>(ifStmt->getCond());
        if (unaryOperator && unaryOperator->getOpcode() == UO_LNot) {
          Violation violation(node, this);
          violationSet.addViolation(violation);
        }
      }
    }
  }
}

const string IfStatementWithNegatedConditionRule::name() const {
  return "if statement with negated condition";
}
