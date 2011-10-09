#include "mo/rule/IfStatementWithNegatedConditionRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/Expr.h>

using namespace clang;

RuleSet IfStatementWithNegatedConditionRule::rules(new IfStatementWithNegatedConditionRule());

bool IfStatementWithNegatedConditionRule::hasElseBlock(clang::IfStmt *ifStmt) {
  return ifStmt && ifStmt->getElse();
}

bool IfStatementWithNegatedConditionRule::hasNegatedCondition(clang::IfStmt *ifStmt) {
  if (ifStmt) {
    BinaryOperator *binaryOperator = dyn_cast<BinaryOperator>(ifStmt->getCond());
    UnaryOperator *unaryOperator = dyn_cast<UnaryOperator>(ifStmt->getCond());
    return (binaryOperator && binaryOperator->getOpcode() == BO_NE) ||
           (unaryOperator && unaryOperator->getOpcode() == UO_LNot);
  }
  return false;
}

void IfStatementWithNegatedConditionRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorUtil::getStmt(node);
  if (stmt) {
    IfStmt *ifStmt = dyn_cast<IfStmt>(stmt);
    if (hasElseBlock(ifStmt) && hasNegatedCondition(ifStmt)) {
      Violation violation(node, this);
      violationSet.addViolation(violation);
    }
  }
}

const string IfStatementWithNegatedConditionRule::name() const {
  return "if statement with negated condition";
}
