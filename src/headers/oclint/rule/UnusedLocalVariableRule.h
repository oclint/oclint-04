#ifndef OCLINT_RULE_UNUSEDLOCALVARIABLERULE_H
#define OCLINT_RULE_UNUSEDLOCALVARIABLERULE_H

#include "oclint/Rule.h"

class UnusedLocalVariableRule : public Rule {
private:
  static RuleSet rules;
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
