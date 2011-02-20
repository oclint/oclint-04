#include "mo/RuleData.h"
#include "mo/Rule.h"
#include "mo/RuleViolation.h"
#include "mo/exception/MOException.h"

RuleData::RuleData() {
  _rule = 0;
}

Rule* RuleData::getRule() {
  return _rule;
}

void RuleData::setRule(Rule* rule) {
  _rule = rule;
}

void RuleData::addViolation(const RuleViolation& violation) {
  _violations.push_back(violation);
}

int RuleData::numberOfViolations() {
  return _violations.size();
}

const RuleViolation& RuleData::violationAt(int index) {
  if (index >= 0 && index < numberOfViolations()) {
    return _violations.at(index);
  }
  else {
    throw new MOException("Index out of range when getting violation!");
  }
}
