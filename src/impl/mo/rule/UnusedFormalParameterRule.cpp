#include "mo/rule/UnusedFormalParameterRule.h"
#include "mo/ruleset/RuleSet.h"
#include "mo/RuleData.h"
#include "mo/RuleViolation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>

using namespace clang;

RuleSet UnusedFormalParameterRule::rules(new UnusedFormalParameterRule());

void UnusedFormalParameterRule::apply(CXCursor& node, CXCursor& parentNode, RuleData& data) {
  Decl *decl = CursorUtil::getDecl(node);
  if (decl) {
    ParmVarDecl *parameterDecl = dyn_cast<ParmVarDecl>(decl);
    if (parameterDecl) {
      if (!parameterDecl->isUsed()) {
        RuleViolation violation(node, this);
        data.addViolation(violation);
      }
    }
  }
}

const string UnusedFormalParameterRule::name() const {
  return "unused formal parameter";
}
