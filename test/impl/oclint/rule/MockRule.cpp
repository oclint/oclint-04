#include "oclint/rule/MockRule.h"
#include "oclint/RuleSet.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/util/CursorUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

RuleSet MockRule::rules(new MockRule());

MockRule::MockRule() {
  _name = "mock rule";
}

MockRule::MockRule(string name) {
  _name = name;
}

void MockRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  _name = "applied!";
  if (Stmt *stmt = CursorUtil::getStmt(node)) {
    if (isa<SwitchStmt>(stmt)) {
      Violation violation(node, this);
      violationSet.addViolation(violation);
    }
  }
  if (node.kind == CXCursor_InvalidFile) {
    Violation violation(node, this);
    violationSet.addViolation(violation);
  }
}

const string MockRule::name() const {
  return _name;
}
