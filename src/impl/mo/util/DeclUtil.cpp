#include "mo/util/DeclUtil.h"
#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

bool DeclUtil::isObjCMethodDeclaredInSuperClass(ObjCMethodDecl *decl) {
  if (decl && !isObjCMethodDeclLocatedInInterfaceContainer(decl)) {
    Selector selector = decl->getSelector();
    ObjCInterfaceDecl *interfaceDecl = decl->getClassInterface();
    if (interfaceDecl) {
      ObjCInterfaceDecl *superInterface = interfaceDecl->getSuperClass();
      return superInterface && superInterface->lookupInstanceMethod(selector);
    }
  }
  return false;
}

bool DeclUtil::isObjCMethodDeclaredInProtocol(ObjCMethodDecl *decl) {
  if (decl && !isObjCMethodDeclLocatedInInterfaceContainer(decl)) {
    Selector selector = decl->getSelector();
    ObjCInterfaceDecl *interfaceDecl = decl->getClassInterface();
    if (interfaceDecl) {
      for (ObjCProtocolList::iterator protocol = interfaceDecl->protocol_begin(), protocolEnd = interfaceDecl->protocol_end(); protocol != protocolEnd; protocol++) {
        ObjCProtocolDecl *protocolDecl = (ObjCProtocolDecl *)*protocol;
        if (protocolDecl->lookupInstanceMethod(selector)) {
          return true;
        }
      }
    }
  }
  return false;
}

bool DeclUtil::isObjCMethodDeclLocatedInInterfaceContainer(ObjCMethodDecl *decl) {
  if (decl) {
    DeclContext *context = decl->getDeclContext();
    return isa<ObjCInterfaceDecl>(context) || isa<ObjCProtocolDecl>(context) || isa<ObjCCategoryDecl>(context);
  }
  return false;
}

bool DeclUtil::isCppMethodDeclLocatedInCppRecordDecl(CXXMethodDecl *decl) {
  return decl && (!decl->hasBody() || isa<CXXRecordDecl>(decl->getLexicalDeclContext()));
}