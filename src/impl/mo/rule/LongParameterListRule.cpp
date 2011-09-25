#include "mo/rule/LongParameterListRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

RuleSet LongParameterListRule::rules(new LongParameterListRule());

void LongParameterListRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Decl *decl = CursorUtil::getDecl(node);
  if (decl) {
    ObjCMethodDecl *objcMethodDecl = dyn_cast<ObjCMethodDecl>(decl);
    if (objcMethodDecl) {
      // Question: what's the difference between 
      // ObjCMethodDecl->param_size() 
      // and 
      // ObjCMethodDecl->getNumSelectorArgs() ?
      if (objcMethodDecl->getNumSelectorArgs() > 3) {
        Violation violation(node, this);
        violationSet.addViolation(violation);
      }
    }
    
    FunctionDecl *cppMethodDecl = dyn_cast<FunctionDecl>(decl);
    if (cppMethodDecl) {
      
    }
  }
}

const string LongParameterListRule::name() const {
  return "long parameter list";
}
