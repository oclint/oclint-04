#include "mo/rule/UnusedLocalVariableRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/DeclUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/DeclObjC.h>

using namespace clang;

RuleSet UnusedLocalVariableRule::rules(new UnusedLocalVariableRule());

bool UnusedLocalVariableRule::isObjCMethodDeclaration(DeclContext *context) {
  ObjCMethodDecl *decl = dyn_cast<ObjCMethodDecl>(context);
  return DeclUtil::isObjCMethodDeclLocatedInInterfaceContainer(decl);
}

bool UnusedLocalVariableRule::isObjCOverrideMethod(DeclContext *context) {
  ObjCMethodDecl *decl = dyn_cast<ObjCMethodDecl>(context);
  return DeclUtil::isObjCMethodDeclaredInSuperClass(decl) || DeclUtil::isObjCMethodDeclaredInProtocol(decl);
}

bool UnusedLocalVariableRule::isCppFunctionDeclaration(DeclContext *context) {
  FunctionDecl *decl = dyn_cast<FunctionDecl>(context);
  return isa<CXXRecordDecl>(context) || (decl && !decl->hasBody());
}

bool UnusedLocalVariableRule::isCppOverrideFunction(DeclContext *context) {
  CXXMethodDecl *decl = dyn_cast<CXXMethodDecl>(context);
  if (decl) {
    return decl->isVirtual();
  }
  return false;
}

bool UnusedLocalVariableRule::isExistingByContract(DeclContext *context) {
  return isObjCMethodDeclaration(context) || 
         isObjCOverrideMethod(context) || 
         isCppFunctionDeclaration(context) || 
         isCppOverrideFunction(context);
}

bool UnusedLocalVariableRule::isExistingByContract(VarDecl *decl) {
  if (isa<ParmVarDecl>(decl)) {
    DeclContext *lexicalContext = decl->getLexicalDeclContext();
    while (lexicalContext) {
      if (isExistingByContract(lexicalContext)) {
        return true;
      }
      lexicalContext = lexicalContext->getLexicalParent();
    }
  }
  
  return false;
}

void UnusedLocalVariableRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
  if (decl) {
    VarDecl *valDecl = dyn_cast<VarDecl>(decl);
    if (valDecl && !valDecl->isUsed() && !valDecl->isStaticDataMember() && !isExistingByContract(valDecl)) {
      Violation violation(node, this);
      violationSet.addViolation(violation);
    }
  }
}

const string UnusedLocalVariableRule::name() const {
  return "unused local variable";
}
