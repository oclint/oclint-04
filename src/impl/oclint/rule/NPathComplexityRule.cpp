#include "oclint/rule/NPathComplexityRule.h"
#include "oclint/RuleSet.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/NPathComplexityMeasurement.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

using namespace clang;

#define DEFAULT_MAX_ALLOWED_NPATH 200

RuleSet NPathComplexityRule::rules(new NPathComplexityRule());

int NPathComplexityRule::maxAllowedNPath() {
  string key = "NPATH_COMPLEXITY";
  return RuleConfiguration::hasKey(key) ? atoi(RuleConfiguration::valueForKey(key).c_str()) : DEFAULT_MAX_ALLOWED_NPATH;
}

void NPathComplexityRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorHelper::getDecl(node);
  if (decl) {
    if (isa<ObjCMethodDecl>(decl) || isa<FunctionDecl>(decl)) {
      int npath = NPathComplexityMeasurement::getNPathOfCursor(node);
      if (npath > maxAllowedNPath()) {
        Violation violation(node, this);
        violationSet.addViolation(violation);
      }
    }
  }
}

const string NPathComplexityRule::name() const {
  return "high npath complexity";
}
