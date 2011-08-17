#include "mo/Violation.h"
#include "mo/Rule.h"

Violation::Violation(const CXCursor& currentNode, Rule *violatedRule) {
  cursor = currentNode;
  rule = violatedRule;
}
