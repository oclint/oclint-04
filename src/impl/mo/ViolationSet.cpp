#include "mo/ViolationSet.h"
#include "mo/Violation.h"

void ViolationSet::addViolation(const Violation& violation) {
  _violations.push_back(violation);
}

int ViolationSet::numberOfViolations() const {
  return _violations.size();
}
const vector<Violation> ViolationSet::getViolations() const {
  return _violations;
}
