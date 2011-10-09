#include "mo/rule/LongParameterListRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/DeclUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

#define DEFAULT_MAX_ALLOWED_PARAMS 3

RuleSet LongParameterListRule::rules(new LongParameterListRule());

int LongParameterListRule::numberOfParameters(Decl *decl) {
  if (decl) {
    ObjCMethodDecl *objcMethodDecl = dyn_cast<ObjCMethodDecl>(decl);
    if (objcMethodDecl && !DeclUtil::isObjCMethodDeclaredInSuperClass(objcMethodDecl) && !DeclUtil::isObjCMethodDeclaredInProtocol(objcMethodDecl)) {
      return objcMethodDecl->getNumSelectorArgs();
    }
    
    FunctionDecl *cppMethodDecl = dyn_cast<FunctionDecl>(decl);
    if (cppMethodDecl) {
      return cppMethodDecl->getNumParams();
    }
  }
  return 0;
}

void LongParameterListRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
  if (numberOfParameters(decl) > DEFAULT_MAX_ALLOWED_PARAMS) {
    Violation violation(node, this);
    violationSet.addViolation(violation);
  }
}

const string LongParameterListRule::name() const {
  return "long parameter list";
}
