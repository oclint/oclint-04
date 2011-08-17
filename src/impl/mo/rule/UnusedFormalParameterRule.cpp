#include "mo/rule/UnusedFormalParameterRule.h"
#include "mo/ruleset/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>

using namespace clang;

RuleSet UnusedFormalParameterRule::rules(new UnusedFormalParameterRule());

void UnusedFormalParameterRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
  if (decl) {
    ParmVarDecl *parameterDecl = dyn_cast<ParmVarDecl>(decl);
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

const string UnusedFormalParameterRule::name() const {
  return "unused formal parameter";
}
