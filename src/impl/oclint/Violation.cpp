#include "oclint/Violation.h"
#include "oclint/Rule.h"

Violation::Violation(const CXCursor& currentNode, Rule *violatedRule, const string& detailDescription) : description(detailDescription) {
  cursor = currentNode;
  rule = violatedRule;
}
