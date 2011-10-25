#ifndef OCLINT_VIOLATION_H
#define OCLINT_VIOLATION_H

#include <clang-c/Index.h>

class Rule;

class Violation {
public:
  CXCursor cursor;
  const Rule *rule;

  Violation(const CXCursor& currentNode, Rule *violatedRule);
};

#endif
