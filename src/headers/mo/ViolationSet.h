#ifndef MO_VIOLATIONSET_H
#define MO_VIOLATIONSET_H

#include <vector>

using namespace std;

class Violation;

class ViolationSet {
private:
  vector<Violation> _violations;
  
public:
  void addViolation(const Violation& violation);
  int numberOfViolations() const;
  const vector<Violation> getViolations() const;
};

#endif
