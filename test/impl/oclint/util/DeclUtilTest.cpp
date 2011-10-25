#include "oclint/util/DeclUtilTest.h"
#include "oclint/util/DeclUtil.h"
#include "oclint/util/CursorExtractionUtil.h"
#include "oclint/util/CursorUtil.h"
#include "oclint/StringSourceCode.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/DeclCXX.h>

using namespace clang;

void DeclUtilTest::testObjCMethodDeclaredInCurrentClass() {
  StringSourceCode strCode("\
  @interface BaseClass\n- (void)aMethod:(int)a;\n@end\n\
  @interface SubClass : BaseClass\n- (void)bMethod:(int)a;\n@end\n\
  @implementation SubClass\n- (void)bMethod:(int)a {}\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  }, -1);
  Decl *objCMethodDecl = CursorUtil::getDecl(cursorPair.first);
  TS_ASSERT(!DeclUtil::isObjCMethodDeclaredInSuperClass(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
  TS_ASSERT(!DeclUtil::isObjCMethodDeclaredInProtocol(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclUtilTest::testObjCMethodDeclaredInSuperClass() {
  StringSourceCode strCode("\
  @interface BaseClass\n- (void)aMethod:(int)a;\n@end\n\
  @interface SubClass : BaseClass\n@end\n\
  @implementation SubClass\n- (void)aMethod:(int)a {}\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  }, -1);
  Decl *objCMethodDecl = CursorUtil::getDecl(cursorPair.first);
  TS_ASSERT(DeclUtil::isObjCMethodDeclaredInSuperClass(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclUtilTest::testObjCMethodDeclaredInProtocol() {
  StringSourceCode strCode("\
  @protocol AProtocol\n- (void)aMethod:(int)a;\n@end\n\
  @interface AClass <AProtocol>\n@end\n\
  @implementation AClass\n- (void)aMethod:(int)a {}\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  }, -1);
  Decl *objCMethodDecl = CursorUtil::getDecl(cursorPair.first);
  TS_ASSERT(DeclUtil::isObjCMethodDeclaredInProtocol(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclUtilTest::testObjCMethodDeclLocatedInInterface() {
  StringSourceCode strCode("@interface AnInterface\n- (void)aMethod:(int)a;\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  });
  Decl *objCMethodDecl = CursorUtil::getDecl(cursorPair.first);
  TS_ASSERT(DeclUtil::isObjCMethodDeclLocatedInInterfaceContainer(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclUtilTest::testObjCMethodDeclLocatedInProtocol() {
  StringSourceCode strCode("@protocol AProtocol\n- (void)aMethod:(int)a;\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  });
  Decl *objCMethodDecl = CursorUtil::getDecl(cursorPair.first);
  TS_ASSERT(DeclUtil::isObjCMethodDeclLocatedInInterfaceContainer(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclUtilTest::testObjCMethodDeclLocatedInCategory() {
  StringSourceCode strCode("@interface AnInterface\n- (void)aMethod:(int)a;\n@end\n\
  @interface AnInterface (ACategory)\n-(void)bMethod:(int)b;\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  }, -1);
  Decl *objCMethodDecl = CursorUtil::getDecl(cursorPair.first);
  TS_ASSERT(DeclUtil::isObjCMethodDeclLocatedInInterfaceContainer(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclUtilTest::testObjCMethodDeclLocatedInImplementation() {
  StringSourceCode strCode("@interface AnInterface\n- (void)aMethod:(int)a;\n@end\n\
  @implementation AnInterface\n-(void)bMethod:(int)b;\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  }, -1);
  Decl *objCMethodDecl = CursorUtil::getDecl(cursorPair.first);
  TS_ASSERT(!DeclUtil::isObjCMethodDeclLocatedInInterfaceContainer(dyn_cast<ObjCMethodDecl>(objCMethodDecl)));
}

void DeclUtilTest::testCppMethodDeclLocatedInCppDeclaration() {
  StringSourceCode strCode("class AClass { int aMethod(int a); };\n\
  int AClass::aMethod(int a) { return 0; }", "cpp");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<CXXMethodDecl>(decl);
  });
  Decl *cppMethodDecl = CursorUtil::getDecl(cursorPair.first);
  TS_ASSERT(DeclUtil::isCppMethodDeclLocatedInCppRecordDecl(dyn_cast<CXXMethodDecl>(cppMethodDecl)));
}

void DeclUtilTest::testCppMethodDeclHasNoBody() {
  StringSourceCode strCode("class AClass { int aMethod(int a); };", "cpp");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<CXXMethodDecl>(decl);
  });
  Decl *cppMethodDecl = CursorUtil::getDecl(cursorPair.first);
  TS_ASSERT(DeclUtil::isCppMethodDeclLocatedInCppRecordDecl(dyn_cast<CXXMethodDecl>(cppMethodDecl)));
}
