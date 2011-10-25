#ifndef OCLINT_RULE_CYCLOMATICCOMPLEXITYRULE_H
#define OCLINT_RULE_CYCLOMATICCOMPLEXITYRULE_H

#include "oclint/Rule.h"

class CyclomaticComplexityRule : public Rule {
private:
  static RuleSet rules;
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
