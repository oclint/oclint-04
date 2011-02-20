#ifndef MO_RULEDATA_H
#define MO_RULEDATA_H

#include <vector>

using namespace std;

class Rule;
class RuleViolation;

class RuleData {
private:
  Rule* _rule;
  vector<RuleViolation> _violations;
  
public:
  RuleData();
  
  Rule* getRule();
  void setRule(Rule* rule);
  
  void addViolation(const RuleViolation& violation);
  int numberOfViolations();
  const RuleViolation& violationAt(int index);
};



#endif
