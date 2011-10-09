#include "mo/RuleSet.h"
#include "mo/Rule.h"

vector<Rule*>* RuleSet::_rules = NULL;

RuleSet::RuleSet(Rule* rule) {
  if (_rules == NULL) {
    _rules = new vector<Rule*>();
  }
  _rules->push_back(rule);
}

int RuleSet::numberOfRules() {
  return _rules->size();
}

void RuleSet::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  for (int index = 0, numRules = numberOfRules(); index != numRules; index++) {
    _rules->at(index)->apply(node, parentNode, violationSet);
  }
}
