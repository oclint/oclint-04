#ifndef MO_RULE_CONSTANTIFSTATEMENTRULE_H
#define MO_RULE_CONSTANTIFSTATEMENTRULE_H

#include "mo/Rule.h"

class ConstantIfStatementRule : public Rule {
private:
  static RuleSet rules;
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
