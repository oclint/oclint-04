#ifndef MO_SWITCHSTATEMENTRULE_H
#define MO_SWITCHSTATEMENTRULE_H

#include "mo/Rule.h"

class SwitchStatementRule : public Rule {
public:
  void apply(CXCursor node, CXCursor parentNode, RuleData& data);
  const string name();
};

#endif
