#include "oclint/rule/UnusedMethodParameterRule.h"
#include "oclint/RuleSet.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/DeclHelper.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/DeclObjC.h>

using namespace clang;

RuleSet UnusedMethodParameterRule::rules(new UnusedMethodParameterRule());

bool UnusedMethodParameterRule::isFunctionDeclaration(DeclContext *context) {
  FunctionDecl *decl = dyn_cast<FunctionDecl>(context);
  return decl && !decl->doesThisDeclarationHaveABody();
}

bool UnusedMethodParameterRule::isBlockDeclaration(DeclContext *context) {
  return dyn_cast<BlockDecl>(context);
}

bool UnusedMethodParameterRule::isObjCMethodDeclaration(DeclContext *context) {
  ObjCMethodDecl *decl = dyn_cast<ObjCMethodDecl>(context);
  return DeclHelper::isObjCMethodDeclLocatedInInterfaceContainer(decl);
}

bool UnusedMethodParameterRule::isObjCOverrideMethod(DeclContext *context) {
  ObjCMethodDecl *decl = dyn_cast<ObjCMethodDecl>(context);
  return DeclHelper::isObjCMethodDeclaredInSuperClass(decl) || DeclHelper::isObjCMethodDeclaredInProtocol(decl);
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
  return isFunctionDeclaration(context) ||
         isBlockDeclaration(context) ||
         isObjCMethodDeclaration(context) || 
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
  Decl *decl = CursorHelper::getDecl(node);
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
