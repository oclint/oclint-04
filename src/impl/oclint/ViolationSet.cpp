#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/Rule.h"

void ViolationSet::addViolation(const Violation& violation) {
  _violations.push_back(violation);
}

void ViolationSet::addViolation(const CXCursor& node, Rule *rule, const string& description) {
  Violation violation(node, rule, description);
  _violations.push_back(violation);
}

int ViolationSet::numberOfViolations() const {
  return _violations.size();
}

const vector<Violation> ViolationSet::getViolations() const {
  return _violations;
}
