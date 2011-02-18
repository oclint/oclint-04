#include "mo/rule/MockRule.h"
#include "mo/RuleViolation.h"

MockRule::MockRule() {
  _name = "mock rule";
}

MockRule::MockRule(string name) {
  _name = name;
}

void MockRule::apply(CXCursor node, CXCursor parentNode, RuleViolation& violation) {
  _name = "applied!";
  violation.addViolation("violation!");
}

const string MockRule::name() {
  return _name;
}
