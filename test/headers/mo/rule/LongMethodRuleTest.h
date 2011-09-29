#include <cxxtest/TestSuite.h>
#include "mo/rule/LongMethodRule.h"

class LongMethodRuleTest : public CxxTest::TestSuite { 
private:
  LongMethodRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testMethodWithSixStatementsIsNotASmell();
  void testMethodWithSevenStatementsIsASmell();
  void testmethodWithEightStatemetnsIsASmell();
  void testMethodWithNestedStatementsShouldNotBeCounted();
};
