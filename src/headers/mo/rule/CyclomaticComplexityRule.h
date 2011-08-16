#ifndef MO_RULE_CYCLOMATICCOMPLEXITYRULE_H
#define MO_RULE_CYCLOMATICCOMPLEXITYRULE_H

#include "mo/Rule.h"

class CyclomaticComplexityRule : public Rule {
private:
  static RuleSet rules;
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
