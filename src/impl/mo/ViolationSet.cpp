#include "mo/ViolationSet.h"
#include "mo/Rule.h"
#include "mo/RuleViolation.h"
#include "mo/exception/MOException.h"

void ViolationSet::addViolation(const RuleViolation& violation) {
  _violations.push_back(violation);
}

int ViolationSet::numberOfViolations() const {
  return _violations.size();
}
const vector<RuleViolation> ViolationSet::getViolations() const {
  return _violations;
}
