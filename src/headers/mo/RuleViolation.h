#ifndef MO_RULEVIOLATION_H
#define MO_RULEVIOLATION_H

#include <clang-c/Index.h>

class Rule;

class RuleViolation {
public:
  CXCursor cursor;
  const Rule *rule;

  RuleViolation(const CXCursor& currentNode, Rule *violatedRule);
};

#endif
