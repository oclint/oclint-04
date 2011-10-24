#include "mo/rule/UnusedLocalVariableRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/DeclUtil.h"

#include <clang/AST/Decl.h>

using namespace clang;

RuleSet UnusedLocalVariableRule::rules(new UnusedLocalVariableRule());

void UnusedLocalVariableRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
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
