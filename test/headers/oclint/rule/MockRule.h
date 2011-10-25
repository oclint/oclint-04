#ifndef OCLINT_RULE_MOCKRULE_H
#define OCLINT_RULE_MOCKRULE_H

#include "oclint/Rule.h"

class MockRule : public Rule {
private:
  string _name;
  static RuleSet rules;
  
public:
  MockRule();
  MockRule(string name);
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
