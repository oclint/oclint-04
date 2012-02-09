#include <cxxtest/TestSuite.h>
#include "oclint/rule/LongMethodRule.h"

class LongMethodRuleTest : public CxxTest::TestSuite { 
private:
  LongMethodRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated, string description);
  void checkRule(string source, bool isViolated, string description);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testMethodWithSixStatementsIsNotASmell();
  void testMethodWithSevenStatementsIsASmell();
  void testmethodWithEightStatemetnsIsASmell();
  void testMethodWithNestedStatementsShouldNotBeCounted();
  void testCppLongMethodShouldReportOnImplementation();
};
