#ifndef MO_RULE_LONGMETHODRULE_H
#define MO_RULE_LONGMETHODRULE_H

#include "mo/Rule.h"

namespace clang {
  class Decl;
}

class LongMethodRule : public Rule {
private:
  static RuleSet rules;
  
  bool isMethodDefination(clang::Decl* decl);
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
