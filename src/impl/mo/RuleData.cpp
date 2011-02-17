#include "mo/RuleData.h"
#include "mo/Rule.h"
#include "mo/RuleViolation.h"

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
