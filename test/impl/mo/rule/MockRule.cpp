#include "mo/rule/MockRule.h"
#include "mo/RuleData.h"
#include "mo/RuleViolation.h"

MockRule::MockRule() {
  _name = "mock rule";
}

MockRule::MockRule(string name) {
  _name = name;
}

void MockRule::apply(CXCursor& node, CXCursor& parentNode, RuleData& data) {
  _name = "applied!";
  RuleViolation violation(clang_getNullCursor(), this);
  data.addViolation(violation);
}

const string MockRule::name() const {
  return _name;
}
