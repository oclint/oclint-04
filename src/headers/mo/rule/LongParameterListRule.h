#ifndef MO_RULE_LONGPARAMETERLISTRULE_H
#define MO_RULE_LONGPARAMETERLISTRULE_H

#include "mo/Rule.h"

class LongParameterListRule : public Rule {
private:
  static RuleSet rules;
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
