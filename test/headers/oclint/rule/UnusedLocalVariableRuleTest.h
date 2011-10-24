#include <cxxtest/TestSuite.h>
#include "oclint/rule/UnusedLocalVariableRule.h"

class UnusedLocalVariableRuleTest : public CxxTest::TestSuite { 
private:
  UnusedLocalVariableRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testUsedLocalVariable();
  void testUnusedLocalVariable();
  void testUnusedLocalVariableWithIntialAssignment();
  void testDeclarationOutsideMethodShouldBeIgnored();
  void testUnusedMethodParameterShouldBeIgnoredInThisRule();
};
