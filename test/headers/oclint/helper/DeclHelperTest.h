#include <cxxtest/TestSuite.h>

class DeclHelperTest : public CxxTest::TestSuite { 
public:  
  void testObjCMethodDeclaredInCurrentClass();
  void testObjCMethodDeclaredInSuperClass();
  void testObjCMethodDeclaredInProtocol();
  void testObjCMethodDeclLocatedInInterface();
  void testObjCMethodDeclLocatedInProtocol();
  void testObjCMethodDeclLocatedInCategory();
  void testObjCMethodDeclLocatedInImplementation();
  void testCppMethodDeclLocatedInCppDeclaration();
  void testCppMethodDeclHasNoBody();
};
