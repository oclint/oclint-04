#include "mo/rule/LongMethodRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/DeclUtil.h"

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
    if (DeclUtil::isCppMethodDeclLocatedInCppRecordDecl(cppMethodDecl)) {
      return false;
    }
    return true;
  }
  return false;
}

void LongMethodRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
  if (isMethodDefination(decl)) {
    CompoundStmt *compoundStmt = dyn_cast<CompoundStmt>(decl->getBody());
    if (compoundStmt && compoundStmt->size() > DEFAULT_MAX_ALLOWED_NUMBER_OF_STATEMENTS) {
      Violation violation(node, this);
      violationSet.addViolation(violation);
    }
  }
}

const string LongMethodRule::name() const {
  return "long method";
}
