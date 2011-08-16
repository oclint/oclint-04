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
  void addViolation(const RuleViolation& violation);
  const int numberOfViolations() const;
  const vector<RuleViolation> getViolations() const;
};



#endif
