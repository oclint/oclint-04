#include "mo/rule/UnusedMethodParameterRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/DeclUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/DeclObjC.h>

using namespace clang;

RuleSet UnusedMethodParameterRule::rules(new UnusedMethodParameterRule());

bool UnusedMethodParameterRule::isObjCMethodDeclaration(DeclContext *context) {
  ObjCMethodDecl *decl = dyn_cast<ObjCMethodDecl>(context);
  return DeclUtil::isObjCMethodDeclLocatedInInterfaceContainer(decl);
}

bool UnusedMethodParameterRule::isObjCOverrideMethod(DeclContext *context) {
  ObjCMethodDecl *decl = dyn_cast<ObjCMethodDecl>(context);
  return DeclUtil::isObjCMethodDeclaredInSuperClass(decl) || DeclUtil::isObjCMethodDeclaredInProtocol(decl);
}

bool UnusedMethodParameterRule::isCppFunctionDeclaration(DeclContext *context) {
  FunctionDecl *decl = dyn_cast<FunctionDecl>(context);
  return isa<CXXRecordDecl>(context) || (decl && !decl->hasBody());
}

bool UnusedMethodParameterRule::isCppOverrideFunction(DeclContext *context) {
  CXXMethodDecl *decl = dyn_cast<CXXMethodDecl>(context);
  if (decl) {
    return decl->isVirtual();
  }
  return false;
}

bool UnusedMethodParameterRule::isExistingByContract(DeclContext *context) {
  return isObjCMethodDeclaration(context) || 
         isObjCOverrideMethod(context) || 
         isCppFunctionDeclaration(context) || 
         isCppOverrideFunction(context);
}

bool UnusedMethodParameterRule::isExistingByContract(ParmVarDecl *decl) {
  DeclContext *lexicalContext = decl->getLexicalDeclContext();
  while (lexicalContext) {
    if (isExistingByContract(lexicalContext)) {
      return true;
    }
    lexicalContext = lexicalContext->getLexicalParent();
  }
  return false;
}

void UnusedMethodParameterRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
  if (decl) {
    ParmVarDecl *varDecl = dyn_cast<ParmVarDecl>(decl);
    if (varDecl && !varDecl->isUsed() && !isExistingByContract(varDecl)) {
      Violation violation(node, this);
      violationSet.addViolation(violation);
    }
  }
}

const string UnusedMethodParameterRule::name() const {
  return "unused method parameter";
}
