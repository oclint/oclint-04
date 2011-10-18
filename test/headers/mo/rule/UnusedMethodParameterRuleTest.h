#include <cxxtest/TestSuite.h>
#include "mo/rule/UnusedMethodParameterRule.h"

class UnusedMethodParameterRuleTest : public CxxTest::TestSuite { 
private:
  UnusedMethodParameterRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testMethodWithUsedParameter();
  void testMethodWithUnusedParameter();
  void testObjCMethodWithUnusedParameter();
  void testFunctionDeclationWithoutDefincationShouldBeIgnored();
  void testCppMethodDeclationWithoutDefincationShouldBeIgnored();
  void testCppMethodInheritanceFromBaseClassShouldBeIgnored();
  void testCppMethodWithoutVirtualInBaseClassIsAViolation();
  void testStaticFunctionShouldBeIgnored();
  void testObjCMethodDeclarationInsideInterfaceShouldBeIgnored();
  void testObjCMethodDeclarationInsideProtocolShouldBeIgnored();
  void testObjCMethodDeclarationInsideCategoryShouldBeIgnored();
  void testObjCMethodInheritanceFromBaseInterfaceShouldBeIgnored();
  void testObjCMethodImplementedForProtocolShouldBeIgnored();
  void testUnusedLocalVariableShouldBeIgnoredInThisRule();
};
