#ifndef MO_RULE_UNUSEDLOCALVARIABLERULE_H
#define MO_RULE_UNUSEDLOCALVARIABLERULE_H

#include "mo/Rule.h"

namespace clang {
  class DeclContext;
}

class UnusedLocalVariableRule : public Rule {
private:
  static RuleSet rules;
  
  bool isObjCInterfaceContainerDecl(clang::DeclContext *context);
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
