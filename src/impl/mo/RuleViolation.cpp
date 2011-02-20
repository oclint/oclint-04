#include "mo/RuleViolation.h"
#include "mo/Rule.h"

RuleViolation::RuleViolation(CXCursor cursor, Rule *rule) {
  _cursor = cursor;
  _rule = rule;
}
