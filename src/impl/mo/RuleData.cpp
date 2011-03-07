#include "mo/RuleData.h"
#include "mo/Rule.h"
#include "mo/RuleViolation.h"
#include "mo/exception/MOException.h"

void RuleData::addRule(Rule *const rule) {
  _rules.push_back(rule);
}

const int RuleData::numberOfRules() const {
  return _rules.size();
}

Rule* RuleData::ruleAt(int index) {
  if (index >= 0 && index < numberOfRules()) {
    return _rules.at(index);
  }
  else {
    throw MOException("Index out of range when getting rule!");
  }
}

void RuleData::addViolation(const RuleViolation& violation) {
  _violations.push_back(violation);
}

const int RuleData::numberOfViolations() const {
  return _violations.size();
}
const vector<RuleViolation> RuleData::getViolations() const {
  return _violations;
}
