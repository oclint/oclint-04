#ifndef MO_MOCKRULE_H
#define MO_MOCKRULE_H

#include "mo/Rule.h"

class MockRule : public Rule {
private:
  string _name;
  
public:
  MockRule();
  MockRule(string name);
  void apply(CXCursor node, CXCursor parentNode, RuleData& data);
  const string name();
};

#endif
