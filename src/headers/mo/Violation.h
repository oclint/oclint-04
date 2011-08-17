#ifndef MO_VIOLATION_H
#define MO_VIOLATION_H

#include <clang-c/Index.h>

class Rule;

class Violation {
public:
  CXCursor cursor;
  const Rule *rule;

  Violation(const CXCursor& currentNode, Rule *violatedRule);
};

#endif
