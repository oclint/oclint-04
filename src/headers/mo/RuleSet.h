#ifndef MO_RULESET_H
#define MO_RULESET_H

#include <vector>

using namespace std;

#include <clang-c/Index.h>

class Rule;
class RuleData;

class RuleSet {
private:
  static vector<Rule*>* _rules;
  
public:
  RuleSet(Rule* rule);
  static int numberOfRules();
  static void apply(CXCursor& node, CXCursor& parentNode, RuleData& data);
};

#endif
