#ifndef OCLINT_RULESET_H
#define OCLINT_RULESET_H

#include <vector>

#include <clang-c/Index.h>

class Rule;
class ViolationSet;

using namespace std;

class RuleSet
{
private:
  static vector<Rule*>* _rules;

public:
  RuleSet(Rule* rule);
  static int numberOfRules();
  static void apply(
    CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
};

#endif
