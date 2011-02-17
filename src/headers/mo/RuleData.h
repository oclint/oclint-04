#ifndef MO_RULEDATA_H
#define MO_RULEDATA_H

#include <vector>

using namespace std;

class Rule;
class RuleViolation;

class RuleData {
private:
  Rule* _rule;
  RuleViolation* _violation;
  
public:
  RuleData();
  
  RuleViolation* getViolation();
  Rule* getRule();
  void setRule(Rule* rule);
  void setViolation(RuleViolation* violation);
};



#endif
