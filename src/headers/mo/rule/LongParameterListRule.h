#ifndef MO_RULE_LONGPARAMETERLISTRULE_H
#define MO_RULE_LONGPARAMETERLISTRULE_H

#include "mo/Rule.h"

namespace clang {
  class Decl;
}

class LongParameterListRule : public Rule {
private:
  static RuleSet rules;
  
  int numberOfParameters(clang::Decl *decl);
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
