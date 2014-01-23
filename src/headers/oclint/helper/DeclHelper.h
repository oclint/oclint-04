#ifndef OCLINT_HELPER_DECLHELPER_H
#define OCLINT_HELPER_DECLHELPER_H

#include <clang-c/Index.h>

namespace clang
{
  class ObjCMethodDecl;
  class CXXMethodDecl;
}

using namespace clang;

class DeclHelper
{
public:
  static bool isObjCMethodDeclaredInSuperClass(ObjCMethodDecl *decl);
  static bool isObjCMethodDeclaredInProtocol(ObjCMethodDecl *decl);
  static bool isObjCMethodDeclLocatedInInterfaceContainer(ObjCMethodDecl *decl);
  static bool isCppMethodDeclLocatedInCppRecordDecl(CXXMethodDecl *decl);
};

#endif
