#ifndef MO_UTIL_DECLUTIL_H
#define MO_UTIL_DECLUTIL_H

#include <clang-c/Index.h>

namespace clang {
  class ObjCMethodDecl;
  class CXXMethodDecl;
}

using namespace clang;

class DeclUtil {
public:
  static bool isObjCMethodDeclaredInSuperClass(ObjCMethodDecl *decl);
  static bool isObjCMethodDeclaredInProtocol(ObjCMethodDecl *decl);
  static bool isObjCMethodDeclLocatedInInterfaceContainer(ObjCMethodDecl *decl);
  static bool isCppMethodDeclLocatedInCppRecordDecl(CXXMethodDecl *decl);
};

#endif
