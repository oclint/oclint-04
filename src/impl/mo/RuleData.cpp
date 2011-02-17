#include "mo/RuleData.h"
#include "mo/Rule.h"
#include "mo/RuleViolation.h"

RuleData::RuleData() {
  _violation = 0;
  _rule = 0;
}

RuleViolation* RuleData::getViolation() {
  return _violation;
}

Rule* RuleData::getRule() {
  return _rule;
}

void RuleData::setRule(Rule* rule) {
  _rule = rule;
}

void RuleData::setViolation(RuleViolation* violation) {
  _violation = violation;
}
