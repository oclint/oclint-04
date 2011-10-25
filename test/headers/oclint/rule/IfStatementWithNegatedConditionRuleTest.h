#include <cxxtest/TestSuite.h>
#include "oclint/rule/IfStatementWithNegatedConditionRule.h"

class IfStatementWithNegatedConditionRuleTest : public CxxTest::TestSuite { 
private:
  IfStatementWithNegatedConditionRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testSimpleIfStatement();
  void testNegativeConditionWithoutElseBlock();
  void testNegativeConditionWithElseBlockWithContent();
  void testNegativeComprisonBetweenTwoValues();
};
