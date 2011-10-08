#include "mo/rule/UnusedLocalVariableRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/DeclObjC.h>

using namespace clang;

RuleSet UnusedLocalVariableRule::rules(new UnusedLocalVariableRule());

bool UnusedLocalVariableRule::isObjCInterfaceContainerDecl(DeclContext *context) {
  return isa<ObjCInterfaceDecl>(context) || isa<ObjCProtocolDecl>(context) || isa<ObjCCategoryDecl>(context);
}

bool UnusedLocalVariableRule::isObjCOverrideMethod(DeclContext *context) {
  ObjCMethodDecl *decl = dyn_cast<ObjCMethodDecl>(context);
  if (decl) {
    Selector selector = decl->getSelector();
    ObjCInterfaceDecl *interfaceDecl = decl->getClassInterface();
    if (interfaceDecl) {
      ObjCInterfaceDecl *superInterface = interfaceDecl->getSuperClass();
      if (superInterface) {
        ObjCMethodDecl *lookedUpInstanceMethod = superInterface->lookupInstanceMethod(selector);
        if (lookedUpInstanceMethod) {
          return true;
        }
      }
      
      for (ObjCProtocolList::iterator protocol = interfaceDecl->protocol_begin(), protocolEnd = interfaceDecl->protocol_end(); protocol != protocolEnd; protocol++) {
        ObjCProtocolDecl *protocolDecl = (ObjCProtocolDecl *)*protocol;
        ObjCMethodDecl *lookedUpInstanceMethod = protocolDecl->lookupInstanceMethod(selector);
        if (lookedUpInstanceMethod) {
          return true;
        }
      }
    }
  }
  return false;
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

bool UnusedLocalVariableRule::isExistingByContract(VarDecl *decl) {
  if (isa<ParmVarDecl>(decl)) {
    DeclContext *context = decl->getDeclContext();
    while (context) {
      if (isObjCInterfaceContainerDecl(context)) {
        return true;
      }
      context = context->getParent();
    }

    DeclContext *lexicalContext = decl->getLexicalDeclContext();
    while (lexicalContext) {
      if (isObjCOverrideMethod(lexicalContext) || isCppFunctionDeclaration(lexicalContext) || isCppOverrideFunction(lexicalContext)) {
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
