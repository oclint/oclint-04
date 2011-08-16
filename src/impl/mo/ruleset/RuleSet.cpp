#include "mo/ruleset/RuleSet.h"
#include "mo/Rule.h"

vector<Rule*>* RuleSet::_rules = NULL;

RuleSet::RuleSet(Rule* rule) {
  if (_rules == NULL) {
    _rules = new vector<Rule*>();
  }
  
  _rules->push_back(rule);
}

int RuleSet::numberOfRules() {
  if (_rules == NULL) {
    _rules = new vector<Rule*>();
  }
  
  return _rules->size();
}

void RuleSet::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  if (_rules == NULL) {
    _rules = new vector<Rule*>();
  } //DRY violation
  
  for (int index = 0, numRules = numberOfRules(); index != numRules; index++) {
    _rules->at(index)->apply(node, parentNode, violationSet);
  }
}
