#include "mo/rule/MockRule.h"
#include "mo/ruleset/RuleSet.h"
#include "mo/RuleData.h"
#include "mo/RuleViolation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

RuleSet MockRule::rules(new MockRule());

MockRule::MockRule() {
  _name = "mock rule";
}

MockRule::MockRule(string name) {
  _name = name;
}

void MockRule::apply(CXCursor& node, CXCursor& parentNode, RuleData& data) {
  _name = "applied!";
  if (Stmt *stmt = CursorUtil::getStmt(node)) {
    if (isa<SwitchStmt>(stmt)) {
      RuleViolation violation(node, this);
      data.addViolation(violation);
    }
  }
  if (node.kind == CXCursor_InvalidFile) {
    RuleViolation violation(node, this);
    data.addViolation(violation);
  }
}

const string MockRule::name() const {
  return _name;
}
