#ifndef MO_SWITCHSTATEMENTRULE_H
#define MO_SWITCHSTATEMENTRULE_H

#include "mo/Rule.h"

class SwitchStatementRule : public Rule {
public:
  void apply(CXCursor node, CXCursor parentNode, RuleViolation& violation);
  const string name();
};

#endif
