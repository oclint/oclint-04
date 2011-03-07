#ifndef MO_SWITCHSTATEMENTRULE_H
#define MO_SWITCHSTATEMENTRULE_H

#include "mo/Rule.h"

class SwitchStatementRule : public Rule {
public:
  virtual void apply(CXCursor node, CXCursor parentNode, RuleData& data);
  virtual string name() const;
};

#endif
