#include "oclint/RuleSet.h"

#include "oclint/Rule.h"

vector<Rule*>* RuleSet::_rules = NULL;

RuleSet::RuleSet(Rule* rule) {
  if (_rules == NULL) {
    _rules = new vector<Rule*>();
  }
  _rules->push_back(rule);
}

int RuleSet::numberOfRules() {
  return _rules == NULL ? 0 : _rules->size();
}

void RuleSet::apply(
  CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  for (int index = 0, numRules = numberOfRules(); index < numRules; index++) {
    _rules->at(index)->apply(node, parentNode, violationSet);
  }
}
