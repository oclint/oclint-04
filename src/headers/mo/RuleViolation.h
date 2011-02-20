#ifndef MO_RULEVIOLATION_H
#define MO_RULEVIOLATION_H

#include <clang-c/Index.h>

class Rule;

class RuleViolation {
public:
  CXCursor _cursor;
  Rule *_rule;

  RuleViolation(CXCursor cursor, Rule *rule);
};

#endif
