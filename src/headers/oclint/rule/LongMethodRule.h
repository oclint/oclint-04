#ifndef OCLINT_RULE_LONGMETHODRULE_H
#define OCLINT_RULE_LONGMETHODRULE_H

#include "oclint/Rule.h"

namespace clang
{
  class Decl;
}

class LongMethodRule : public Rule
{
private:
  static RuleSet rules;

  bool isMethodDefination(clang::Decl* decl);
  bool isMethodDeclarationAndHasBody(clang::Decl* decl);
  bool isMethodNotPureDeclaration(clang::Decl* decl);
  int maxAllowedMethodLength();

public:
  virtual void apply(
    CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
