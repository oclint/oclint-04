#ifndef MO_RULE_UNUSEDLOCALVARIABLERULE_H
#define MO_RULE_UNUSEDLOCALVARIABLERULE_H

#include "mo/Rule.h"

namespace clang {
  class DeclContext;
  class VarDecl;
  class ObjCMethodDecl;
}

using namespace clang;

class UnusedLocalVariableRule : public Rule {
private:
  static RuleSet rules;
  
  bool isObjCMethodDeclaration(DeclContext *context);
  bool isObjCOverrideMethod(DeclContext *context);
  bool isCppFunctionDeclaration(DeclContext *context);
  bool isCppOverrideFunction(DeclContext *context);
  bool isExistingByContract(VarDecl *decl);
  bool isExistingByContract(DeclContext *context);
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
