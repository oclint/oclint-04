#ifndef MO_RULESET_H
#define MO_RULESET_H

#include <vector>

using namespace std;

class Rule;

class RuleSet {
private:
  static vector<Rule*>* _rules;
  
public:
  RuleSet(Rule* rule);
  static int numberOfRules();
  static void emptySet();
};

#endif
