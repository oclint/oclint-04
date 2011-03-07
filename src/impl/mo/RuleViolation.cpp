#include "mo/RuleViolation.h"
#include "mo/Rule.h"

RuleViolation::RuleViolation(const CXCursor& currentNode, Rule *violatedRule) {
  cursor = currentNode;
  rule = violatedRule;
}
