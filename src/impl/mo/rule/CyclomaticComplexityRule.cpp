#include "mo/rule/CyclomaticComplexityRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/CCNCounterUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

using namespace clang;

#define DEFAULT_MAX_ALLOWED_CCN 9

RuleSet CyclomaticComplexityRule::rules(new CyclomaticComplexityRule());

void CyclomaticComplexityRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
  if (decl) {
    if (isa<ObjCMethodDecl>(decl) || isa<FunctionDecl>(decl)) {
      int ccn = CCNCounterUtil::getCCNOfCursor(node);
      if (ccn > DEFAULT_MAX_ALLOWED_CCN) {
        Violation violation(node, this);
        violationSet.addViolation(violation);
      }
    }
  }
}

const string CyclomaticComplexityRule::name() const {
  return "high cyclomatic complexity";
}
