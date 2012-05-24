#ifndef OCLINT_VIOLATION_H
#define OCLINT_VIOLATION_H

#include <string>

#include <clang-c/Index.h>

class Rule;

using namespace std;

class Violation {
public:
  CXCursor cursor;
  const Rule *rule;
  string description;

  Violation(const CXCursor& currentNode, Rule *violatedRule, const string& detailDescription = "");
};

#endif
