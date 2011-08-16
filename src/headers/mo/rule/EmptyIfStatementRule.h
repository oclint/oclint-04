#ifndef MO_RULE_EMPTYIFSTATEMENTRULE_H
#define MO_RULE_EMPTYIFSTATEMENTRULE_H

#include "mo/Rule.h"

class EmptyIfStatementRule : public Rule {
private:
  static RuleSet rules;
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
