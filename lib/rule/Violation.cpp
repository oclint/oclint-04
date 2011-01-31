#include "mo/rule/Violation.h"

void Violation::addViolation(SourceRange sourceRange, AbstractRule* rule, string message) {
  _violations.push_back(new RuleViolation(sourceRange, rule, message));
}

void Violation::addViolation(RuleViolation *violation) {
  _violations.push_back(violation);
}

int Violation::numberOfViolations() {
  return _violations.size();
}

RuleViolation* Violation::violation(int index) {
  if (!indexWithinViolationRange(index)) {
    throw MessageBasedException("Index out of range when trying to get a certain RuleViolation!");
  }
  return _violations.at(index);
}

bool Violation::indexWithinViolationRange(int index) {
  return index >= 0 && index < numberOfViolations();
}
