#ifndef OCLINT_RULE_NPATHCOMPLEXITYRULE_H
#define OCLINT_RULE_NPATHCOMPLEXITYRULE_H

#include "oclint/Rule.h"

class NPathComplexityRule : public Rule {
private:
  static RuleSet rules;
  
  int maxAllowedNPath();
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
