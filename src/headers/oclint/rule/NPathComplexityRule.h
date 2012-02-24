#ifndef OCLINT_RULE_NPATHCOMPLEXITYRULE_H
#define OCLINT_RULE_NPATHCOMPLEXITYRULE_H

#include "oclint/Rule.h"

namespace clang {
  class Decl;
}

class NPathComplexityRule : public Rule {
private:
  static RuleSet rules;
  
  int maxAllowedNPath();
  bool isMethodDefination(clang::Decl* decl);
  bool isMethodNPathHigh(CXCursor& node);
  int getNPathOfCursor(CXCursor& node);
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
