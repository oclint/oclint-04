#include "oclint/rule/LongParameterListRule.h"
#include "oclint/RuleSet.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/DeclHelper.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

#define DEFAULT_MAX_ALLOWED_PARAMS 3

RuleSet LongParameterListRule::rules(new LongParameterListRule());

int LongParameterListRule::maxAllowedNumberOfParameters() {
  string key = "NUMBER_OF_PARAMETERS";
  return RuleConfiguration::hasKey(key) ? atoi(RuleConfiguration::valueForKey(key).c_str()) : DEFAULT_MAX_ALLOWED_PARAMS;
}

int LongParameterListRule::numberOfParameters(Decl *decl) {
  if (decl) {
    ObjCMethodDecl *objcMethodDecl = dyn_cast<ObjCMethodDecl>(decl);
    if (objcMethodDecl && !DeclHelper::isObjCMethodDeclaredInSuperClass(objcMethodDecl) && !DeclHelper::isObjCMethodDeclaredInProtocol(objcMethodDecl)) {
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
  Decl *decl = CursorHelper::getDecl(node);
  if (numberOfParameters(decl) > maxAllowedNumberOfParameters()) {
    Violation violation(node, this);
    violationSet.addViolation(violation);
  }
}

const string LongParameterListRule::name() const {
  return "long parameter list";
}
