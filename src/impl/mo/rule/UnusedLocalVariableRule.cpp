#include "mo/rule/UnusedLocalVariableRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>

using namespace clang;

RuleSet UnusedLocalVariableRule::rules(new UnusedLocalVariableRule());

bool UnusedLocalVariableRule::isObjCInterfaceContainerDecl(DeclContext *context) {
  return isa<ObjCInterfaceDecl>(context) || isa<ObjCProtocolDecl>(context) || isa<ObjCCategoryDecl>(context);
}

void UnusedLocalVariableRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
  if (decl) {
    VarDecl *valDecl = dyn_cast<VarDecl>(decl);
    if (valDecl && !valDecl->isUsed()) {
      DeclContext *context = valDecl->getDeclContext();
      while (context) {
        if (isObjCInterfaceContainerDecl(context)) {
          return;
        }
        context = context->getParent();
      }
      Violation violation(node, this);
      violationSet.addViolation(violation);
    }
  }
}

const string UnusedLocalVariableRule::name() const {
  return "unused local variable";
}
