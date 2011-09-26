#include "mo/rule/LongMethodRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

using namespace clang;

#define DEFAULT_MAX_ALLOWED_NUMBER_OF_STATEMENTS 6

RuleSet LongMethodRule::rules(new LongMethodRule());

void LongMethodRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  int numberOfStatements = 0;
  Decl *decl = CursorUtil::getDecl(node);
  if (decl && (isa<ObjCMethodDecl>(decl) || isa<FunctionDecl>(decl)) && decl->hasBody()) {
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
