#include <cxxtest/TestSuite.h>
#include "mo/rule/UnusedLocalVariableRule.h"

class UnusedLocalVariableRuleTest : public CxxTest::TestSuite { 
private:
  UnusedLocalVariableRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testMethodWithUsedParameter();
  void testMethodWithUnusedParameter();
  void testObjCMethodWithUnusedParameter();
  void testUsedLocalVariable();
  void testUnusedLocalVariable();
  void testUnusedLocalVariableWithIntialAssignment();
  
  void testFunctionDeclationWithoutDefincationShouldBeIgnored();
  void testCppMethodDeclationWithoutDefincationShouldBeIgnored();
  void testCppMethodInheritanceFromBaseClassShouldBeIgnored();
  void testCppMethodWithoutVirtualInBaseClassIsAViolation();
  void testSaticFunctionShouldBeIgnored();
  void testObjCMethodDeclarationInsideInterfaceShouldBeIgnored();
  void testObjCMethodDeclarationInsideProtocolShouldBeIgnored();
  void testObjCMethodDeclarationInsideCategoryShouldBeIgnored();
  void testObjCMethodInheritanceFromBaseInterfaceShouldBeIgnored();
  void testObjCMethodImplementedForProtocolShouldBeIgnored();
};
