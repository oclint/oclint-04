#ifndef MO_RULE_UNUSEDLOCALVARIABLERULE_H
#define MO_RULE_UNUSEDLOCALVARIABLERULE_H

#include "mo/Rule.h"

class UnusedLocalVariableRule : public Rule {
private:
  static RuleSet rules;
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
