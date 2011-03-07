#ifndef MO_RULEDATA_H
#define MO_RULEDATA_H

#include <vector>

using namespace std;

class Rule;
class RuleViolation;

class RuleData {
private:
  vector<Rule*> _rules;
  vector<RuleViolation> _violations;
  
public:
  void addRule(Rule *const rule);
  //later I will use dynamically load rules
  // can i use a const pointer here?
  
  const int numberOfRules() const;
  Rule* ruleAt(int index);
  
  void addViolation(const RuleViolation& violation);
  const int numberOfViolations() const;
  const vector<RuleViolation> getViolations() const;
};



#endif
