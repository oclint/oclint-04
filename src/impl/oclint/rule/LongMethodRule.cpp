#include "oclint/rule/LongMethodRule.h"
#include "oclint/RuleSet.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/DeclHelper.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

using namespace clang;

#define DEFAULT_MAX_ALLOWED_NUMBER_OF_STATEMENTS 6

RuleSet LongMethodRule::rules(new LongMethodRule());

bool LongMethodRule::isMethodDefination(Decl* decl) {
  if (decl && (isa<ObjCMethodDecl>(decl) || isa<FunctionDecl>(decl)) && decl->hasBody()) {
    CXXMethodDecl *cppMethodDecl = dyn_cast<CXXMethodDecl>(decl);
    if (DeclHelper::isCppMethodDeclLocatedInCppRecordDecl(cppMethodDecl)) {
      return false;
    }
    return true;
  }
  return false;
}

int LongMethodRule::maxAllowedMethodLength() {
  string key = "METHOD_LENGTH";
  return RuleConfiguration::hasKey(key) ? atoi(RuleConfiguration::valueForKey(key).c_str()) : DEFAULT_MAX_ALLOWED_NUMBER_OF_STATEMENTS;
}

void LongMethodRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorHelper::getDecl(node);
  if (isMethodDefination(decl)) {
    CompoundStmt *compoundStmt = dyn_cast<CompoundStmt>(decl->getBody());
    if (compoundStmt && compoundStmt->size() > maxAllowedMethodLength()) {
      Violation violation(node, this);
      violationSet.addViolation(violation);
    }
  }
}

const string LongMethodRule::name() const {
  return "long method";
}
