#include "mo/RuleViolation.h"
#include "mo/exception/MOException.h"

void RuleViolation::addViolation(const string& violationMessage) {
  _violations.push_back(violationMessage);
}

int RuleViolation::numberOfViolations() {
  return _violations.size();
}

const string& RuleViolation::violationAt(int index) {
  if (index >= 0 && index < numberOfViolations()) {
    return _violations.at(index);
  }
  else {
    throw new MOException("Index out of range when getting violation!");
  }
}
