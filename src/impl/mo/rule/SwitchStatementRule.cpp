#include "mo/rule/SwitchStatementRule.h"
#include "mo/RuleData.h"
#include "mo/RuleViolation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

SwitchStatementRule::SwitchStatementRule() {
  _name = "switch statement"; 
}

void SwitchStatementRule::apply(CXCursor& node, CXCursor& parentNode, RuleData& data) {
  if (Stmt *stmt = CursorUtil::getStmt(node)) {
    if (isa<SwitchStmt>(stmt)) {
      RuleViolation violation(node, this);
      data.addViolation(violation);
    }
  }
}

const string& SwitchStatementRule::name() const {
  return _name;
  // return string("switch statement");
  // to avoid warning: returning reference to temporary 
  // I store this into a member.
  // But is it a better to achieve this?
}
