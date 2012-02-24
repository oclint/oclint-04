#ifndef OCLINT_VIOLATION_H
#define OCLINT_VIOLATION_H

#include <clang-c/Index.h>

#include <string>

using namespace std;

class Rule;

class Violation {
public:
  CXCursor cursor;
  const Rule *rule;
  string description;

  Violation(const CXCursor& currentNode, Rule *violatedRule, const string& detailDescription = "");
};

#endif
