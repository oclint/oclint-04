#include "mo/rule/CyclomaticComplexityRule.h"
#include "mo/ruleset/RuleSet.h"
#include "mo/RuleData.h"
#include "mo/RuleViolation.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/CCNCounterUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

using namespace clang;

RuleSet CyclomaticComplexityRule::rules(new CyclomaticComplexityRule());

void CyclomaticComplexityRule::apply(CXCursor& node, CXCursor& parentNode, RuleData& data) {
  Decl *decl = CursorUtil::getDecl(node);
  if (decl) {
    if (isa<ObjCMethodDecl>(decl) || isa<CXXMethodDecl>(decl) || isa<FunctionDecl>(decl)) {
      int ccn = CCNCounterUtil::getCCNOfCursor(node);
      if (ccn > 9) {
        RuleViolation violation(node, this);
        data.addViolation(violation);
      }
    }
  }
}

const string CyclomaticComplexityRule::name() const {
  return "high cyclomatic complexity";
}
