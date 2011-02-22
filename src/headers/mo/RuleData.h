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
  void addRule(Rule* rule);
  const int numberOfRules();
  Rule* ruleAt(int index);
  
  void addViolation(const RuleViolation& violation);
  const int numberOfViolations();
  const RuleViolation& violationAt(int index);
};



#endif
