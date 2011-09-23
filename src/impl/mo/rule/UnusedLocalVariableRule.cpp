#include "mo/rule/UnusedLocalVariableRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>

using namespace clang;

RuleSet UnusedLocalVariableRule::rules(new UnusedLocalVariableRule());

void UnusedLocalVariableRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
  if (decl) {
    VarDecl *parameterDecl = dyn_cast<VarDecl>(decl);
    if (parameterDecl) {
      if (!parameterDecl->isUsed()) {
        DeclContext *context = parameterDecl->getDeclContext();
        do {
          if (isa<ObjCInterfaceDecl>(context)) {
            return;
          }
          context = context->getParent();
        } while (context);
        Violation violation(node, this);
        violationSet.addViolation(violation);
      }
    }
  }
}

const string UnusedLocalVariableRule::name() const {
  return "unused local variable";
}
