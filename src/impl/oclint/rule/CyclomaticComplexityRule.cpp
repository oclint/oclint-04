#include "oclint/rule/CyclomaticComplexityRule.h"
#include "oclint/RuleSet.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/CyclomaticComplexityMeasurement.h"
#include "oclint/helper/StringHelper.h"

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

int CyclomaticComplexityRule::maxAllowedCCN() {
  string key = "CYCLOMATIC_COMPLEXITY";
  return RuleConfiguration::hasKey(key) ? atoi(RuleConfiguration::valueForKey(key).c_str()) : DEFAULT_MAX_ALLOWED_CCN;
}

void CyclomaticComplexityRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorHelper::getDecl(node);
  if (decl && (isa<ObjCMethodDecl>(decl) || isa<FunctionDecl>(decl))) {
    int ccn = CyclomaticComplexityMeasurement::getCCNOfCursor(node);
    if (ccn > maxAllowedCCN()) {
      string description = "Cyclomatic Complexity Number " + StringHelper::convertIntToString(ccn) + " exceeds limit of " + StringHelper::convertIntToString(maxAllowedCCN());
      violationSet.addViolation(node, this, description);
    }
  }
}

const string CyclomaticComplexityRule::name() const {
  return "high cyclomatic complexity";
}
