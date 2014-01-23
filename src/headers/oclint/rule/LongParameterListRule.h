#ifndef OCLINT_RULE_LONGPARAMETERLISTRULE_H
#define OCLINT_RULE_LONGPARAMETERLISTRULE_H

#include "oclint/Rule.h"

namespace clang
{
  class Decl;
}

class LongParameterListRule : public Rule
{
private:
  static RuleSet rules;

  int numberOfParameters(clang::Decl *decl);
  int maxAllowedNumberOfParameters();

public:
  virtual void apply(
    CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
