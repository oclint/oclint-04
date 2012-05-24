#include "oclint/rule/LongMethodRule.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

#include "oclint/RuleSet.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/DeclHelper.h"
#include "oclint/helper/StringHelper.h"

using namespace clang;

#define DEFAULT_MAX_ALLOWED_NUMBER_OF_STATEMENTS 6

RuleSet LongMethodRule::rules(new LongMethodRule());

bool LongMethodRule::isMethodDeclarationAndHasBody(Decl* decl) {
  return (isa<ObjCMethodDecl>(decl) || isa<FunctionDecl>(decl)) && decl->hasBody();
}

bool LongMethodRule::isMethodNotPureDeclaration(Decl* decl) {
  return !DeclHelper::isCppMethodDeclLocatedInCppRecordDecl(dyn_cast<CXXMethodDecl>(decl));
}

bool LongMethodRule::isMethodDefination(Decl* decl) {
  return decl && isMethodDeclarationAndHasBody(decl) && isMethodNotPureDeclaration(decl);
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
      string description = "Method has " + StringHelper::convertIntToString(compoundStmt->size()) + " statements exceeds limit of " + StringHelper::convertIntToString(maxAllowedMethodLength()) + ".";
      violationSet.addViolation(node, this, description);
    }
  }
}

const string LongMethodRule::name() const {
  return "long method";
}
