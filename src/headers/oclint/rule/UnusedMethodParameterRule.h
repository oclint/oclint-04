#ifndef OCLINT_RULE_UNUSEDMETHODPARAMETERRULE_H
#define OCLINT_RULE_UNUSEDMETHODPARAMETERRULE_H

#include "oclint/Rule.h"

namespace clang
{
  class DeclContext;
  class ParmVarDecl;
}

using namespace clang;

class UnusedMethodParameterRule : public Rule
{
private:
  static RuleSet rules;

  bool isFunctionDeclaration(DeclContext *context);
  bool isBlockDeclaration(DeclContext *context);
  bool isObjCMethodDeclaration(DeclContext *context);
  bool isObjCOverrideMethod(DeclContext *context);
  bool isCppFunctionDeclaration(DeclContext *context);
  bool isCppOverrideFunction(DeclContext *context);
  bool isExistingByContract(ParmVarDecl *decl);
  bool isExistingByContract(DeclContext *context);

public:
  virtual void apply(
    CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
