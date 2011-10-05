#include "mo/rule/NPathComplexityRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/NPathComplexityMeasurement.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

using namespace clang;

#define DEFAULT_MAX_ALLOWED_NPATH 200

RuleSet NPathComplexityRule::rules(new NPathComplexityRule());

void NPathComplexityRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
  if (decl) {
    if (isa<ObjCMethodDecl>(decl) || isa<FunctionDecl>(decl)) {
      int npath = NPathComplexityMeasurement::getNPathOfCursor(node);
      if (npath > DEFAULT_MAX_ALLOWED_NPATH) {
        Violation violation(node, this);
        violationSet.addViolation(violation);
      }
    }
  }
}

const string NPathComplexityRule::name() const {
  return "high npath complexity";
}
