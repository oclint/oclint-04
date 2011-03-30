#ifndef MO_EMPTYIFSTATEMENTRULE_H
#define MO_EMPTYIFSTATEMENTRULE_H

#include "mo/Rule.h"

class EmptyIfStatementRule : public Rule {
private:
  static RuleSet rules;
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, RuleData& data);
  virtual const string name() const;
};

#endif
