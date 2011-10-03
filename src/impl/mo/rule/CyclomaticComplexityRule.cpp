#include "mo/rule/CyclomaticComplexityRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/CyclomaticComplexityMeasurement.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

using namespace clang;

#define DEFAULT_MAX_ALLOWED_CCN 7

/*
 In McBABE, 1976, A Complexity Measure, he suggested a reasonable number of 10,
 However, the statistics in STAMELOS, 2002, Code Quality Analysis in Open 
 Source Software Development describe that, the mean of cyclomatic complexity
 of methods among 100 Linux application's source code is 7.70, so here, we
 use 7 as a default max allow complexity number.
*/

RuleSet CyclomaticComplexityRule::rules(new CyclomaticComplexityRule());

void CyclomaticComplexityRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
  if (decl) {
    if (isa<ObjCMethodDecl>(decl) || isa<FunctionDecl>(decl)) {
      int ccn = CyclomaticComplexityMeasurement::getCCNOfCursor(node);
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
