#include "mo/rule/MockRule.h"

MockRule::MockRule() {
  _name = "mock rule";
}

MockRule::MockRule(string name) {
  _name = name;
}

void MockRule::apply(CXCursor node, CXCursor parentNode, RuleViolation *violation) {
  // :)
}

string MockRule::name() {
  return _name;
}
