#include <cxxtest/TestSuite.h>
#include "mo/rule/UnusedFormalParameterRule.h"

class UnusedFormalParameterRuleTest : public CxxTest::TestSuite { 
private:
  UnusedFormalParameterRule *_rule;
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testMethodWithUsedParameter();
  void testMethodWithUnusedParameter();
  void testObjCMethodWithUnusedParameter();
  void testObjCMethodDeclarationInsideInterface();
  void testUsedLocalVariable();
  void testUnusedLocalVariable();
  void testUnusedLocalVariableWithIntialAssignment();
};
