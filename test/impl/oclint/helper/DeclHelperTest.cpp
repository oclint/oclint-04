#include "oclint/helper/DeclHelperTest.h"
#include "oclint/helper/DeclHelper.h"
#include "oclint/helper/CursorExtractionHelper.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/StringSourceCode.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

using namespace clang;

void DeclHelperTest::testObjCMethodDeclaredInCurrentClass() {
  StringSourceCode strCode("\
  @interface BaseClass\n- (void)aMethod:(int)a;\n@end\n\
  @interface SubClass : BaseClass\n- (void)bMethod:(int)a;\n@end\n\
  @implementation SubClass\n- (void)bMethod:(int)a {}\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  }, -1);
  Decl *objCMethodDecl = CursorHelper::getDecl(cursorPair.first);
  TS_ASSERT(!DeclHelper::isObjCMethodDeclaredInSuperClass(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
  TS_ASSERT(!DeclHelper::isObjCMethodDeclaredInProtocol(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclHelperTest::testObjCMethodDeclaredInSuperClass() {
  StringSourceCode strCode("\
  @interface BaseClass\n- (void)aMethod:(int)a;\n@end\n\
  @interface SubClass : BaseClass\n@end\n\
  @implementation SubClass\n- (void)aMethod:(int)a {}\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  }, -1);
  Decl *objCMethodDecl = CursorHelper::getDecl(cursorPair.first);
  TS_ASSERT(DeclHelper::isObjCMethodDeclaredInSuperClass(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclHelperTest::testObjCMethodDeclaredInProtocol() {
  StringSourceCode strCode("\
  @protocol AProtocol\n- (void)aMethod:(int)a;\n@end\n\
  @interface AClass <AProtocol>\n@end\n\
  @implementation AClass\n- (void)aMethod:(int)a {}\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  }, -1);
  Decl *objCMethodDecl = CursorHelper::getDecl(cursorPair.first);
  TS_ASSERT(DeclHelper::isObjCMethodDeclaredInProtocol(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclHelperTest::testObjCMethodDeclLocatedInInterface() {
  StringSourceCode strCode("@interface AnInterface\n- (void)aMethod:(int)a;\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  });
  Decl *objCMethodDecl = CursorHelper::getDecl(cursorPair.first);
  TS_ASSERT(DeclHelper::isObjCMethodDeclLocatedInInterfaceContainer(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclHelperTest::testObjCMethodDeclLocatedInProtocol() {
  StringSourceCode strCode("@protocol AProtocol\n- (void)aMethod:(int)a;\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  });
  Decl *objCMethodDecl = CursorHelper::getDecl(cursorPair.first);
  TS_ASSERT(DeclHelper::isObjCMethodDeclLocatedInInterfaceContainer(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclHelperTest::testObjCMethodDeclLocatedInCategory() {
  StringSourceCode strCode("@interface AnInterface\n- (void)aMethod:(int)a;\n@end\n\
  @interface AnInterface (ACategory)\n-(void)bMethod:(int)b;\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  }, -1);
  Decl *objCMethodDecl = CursorHelper::getDecl(cursorPair.first);
  TS_ASSERT(DeclHelper::isObjCMethodDeclLocatedInInterfaceContainer(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclHelperTest::testObjCMethodDeclLocatedInImplementation() {
  StringSourceCode strCode("@interface AnInterface\n- (void)aMethod:(int)a;\n@end\n\
  @implementation AnInterface\n-(void)bMethod:(int)b;\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  }, -1);
  Decl *objCMethodDecl = CursorHelper::getDecl(cursorPair.first);
  TS_ASSERT(!DeclHelper::isObjCMethodDeclLocatedInInterfaceContainer(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclHelperTest::testCppMethodDeclLocatedInCppDeclaration() {
  StringSourceCode strCode("class AClass { int aMethod(int a); };\n\
  int AClass::aMethod(int a) { return 0; }", "cpp");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<CXXMethodDecl>(decl);
  });
  Decl *cppMethodDecl = CursorHelper::getDecl(cursorPair.first);
  TS_ASSERT(DeclHelper::isCppMethodDeclLocatedInCppRecordDecl(dyn_cast<CXXMethodDecl>(cppMethodDecl)));
}

void DeclHelperTest::testCppMethodDeclHasNoBody() {
  StringSourceCode strCode("class AClass { int aMethod(int a); };", "cpp");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<CXXMethodDecl>(decl);
  });
  Decl *cppMethodDecl = CursorHelper::getDecl(cursorPair.first);
  TS_ASSERT(DeclHelper::isCppMethodDeclLocatedInCppRecordDecl(dyn_cast<CXXMethodDecl>(cppMethodDecl)));
}
