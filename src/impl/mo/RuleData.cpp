#include "mo/RuleData.h"
#include "mo/Rule.h"
#include "mo/RuleViolation.h"
#include "mo/exception/MOException.h"

void RuleData::addViolation(const RuleViolation& violation) {
  _violations.push_back(violation);
}

const int RuleData::numberOfViolations() const {
  return _violations.size();
}
const vector<RuleViolation> RuleData::getViolations() const {
  return _violations;
}
