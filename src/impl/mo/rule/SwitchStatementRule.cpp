#include "mo/rule/SwitchStatementRule.h"
#include "mo/RuleViolation.h"

void SwitchStatementRule::apply(CXCursor node, CXCursor parentNode, RuleViolation& violation) {
}

const string SwitchStatementRule::name() {
  return "Switch Statement";
}
