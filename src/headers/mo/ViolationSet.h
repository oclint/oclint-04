#ifndef MO_VIOLATIONSET_H
#define MO_VIOLATIONSET_H

#include <vector>

using namespace std;

class RuleViolation;

class ViolationSet {
private:
  vector<RuleViolation> _violations;
  
public:
  void addViolation(const RuleViolation& violation);
  int numberOfViolations() const;
  const vector<RuleViolation> getViolations() const;
};

#endif
