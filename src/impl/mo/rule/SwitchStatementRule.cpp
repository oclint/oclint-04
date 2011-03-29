#include "mo/rule/SwitchStatementRule.h"
#include "mo/RuleData.h"
#include "mo/RuleSet.h"
#include "mo/RuleViolation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

RuleSet SwitchStatementRule::rules(new SwitchStatementRule());

void SwitchStatementRule::apply(CXCursor& node, CXCursor& parentNode, RuleData& data) {
  if (Stmt *stmt = CursorUtil::getStmt(node)) {
    if (isa<SwitchStmt>(stmt)) {
      RuleViolation violation(node, this);
      data.addViolation(violation);
    }
  }
}

const string SwitchStatementRule::name() const {
  return "switch statement";
}
