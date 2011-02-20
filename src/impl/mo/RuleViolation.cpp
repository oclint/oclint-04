#include "mo/RuleViolation.h"
#include "mo/Rule.h"

RuleViolation::RuleViolation(CXCursor currentNode, Rule *violatedRule) {
  cursor = currentNode;
  rule = violatedRule;
}
