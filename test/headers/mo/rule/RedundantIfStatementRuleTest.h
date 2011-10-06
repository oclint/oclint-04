#include <cxxtest/TestSuite.h>
#include "mo/rule/RedundantIfStatementRule.h"

class RedundantIfStatementRuleTest : public CxxTest::TestSuite { 
private:
  RedundantIfStatementRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, string sourceType, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testGoodIfStatement();
  void testIfStatementWithOneThenAndZeroElse();
  void testIfStatementWithZeroThenAndOneElse();
  void testIfStatementWithTrueThenAndFalseElse();
  void testIfStatementWithFalseThenAndTrueElse();
  void testIfStatementWithYesThenAndNoElse();
  void testIfStatementWithNoThenAndYesElse();
  void testIfStatementWithCIntDeclaration();
  void testIfStatementWithCppBooleanDeclaration();
  void testIfStatementWithObjCBOOLDeclaration();
};
