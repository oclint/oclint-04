#include "oclint/rule/UnusedLocalVariableRule.h"
#include "oclint/RuleSet.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/DeclHelper.h"

#include <clang/AST/Decl.h>

using namespace clang;

RuleSet UnusedLocalVariableRule::rules(new UnusedLocalVariableRule());

void UnusedLocalVariableRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorHelper::getDecl(node);
  if (decl) {
    VarDecl *varDecl = dyn_cast<VarDecl>(decl);
    if (varDecl && !varDecl->isUsed() && varDecl->isLocalVarDecl() && !varDecl->isStaticDataMember()) {
      Violation violation(node, this);
      violationSet.addViolation(violation);
    }
  }
}

const string UnusedLocalVariableRule::name() const {
  return "unused local variable";
}
