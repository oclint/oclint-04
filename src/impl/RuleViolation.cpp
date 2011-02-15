#include "mo/RuleViolation.h"

void RuleViolation::addViolation(string violationMessage) {
  _violations.push_back(violationMessage);
}

int RuleViolation::numberOfViolations() {
  return _violations.size();
}
