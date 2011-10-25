#include "oclint/Violation.h"
#include "oclint/Rule.h"

Violation::Violation(const CXCursor& currentNode, Rule *violatedRule) {
  cursor = currentNode;
  rule = violatedRule;
}
