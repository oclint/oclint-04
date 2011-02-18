#ifndef MO_RULEVIOLATION_H
#define MO_RULEVIOLATION_H

#include <string>
#include <vector>

using namespace std;

class RuleViolation {
private:
  vector<string> _violations;

public:
  void addViolation(const string& violationMessage);
  int numberOfViolations();
  const string& violationAt(int index);
};

#endif
