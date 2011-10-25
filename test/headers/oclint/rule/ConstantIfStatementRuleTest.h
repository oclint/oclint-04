#include <cxxtest/TestSuite.h>
#include "oclint/rule/ConstantIfStatementRule.h"

class ConstantIfStatementRuleTest : public CxxTest::TestSuite { 
private:
  ConstantIfStatementRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testGoodConditionExpression();
  void testCompareTwoKnownBoolValuesAlwaysBeTrue();
  void testCompareTwoKnownBoolValuesAlwaysBeFalse();
  void testIntegerAlwaysConstant();
  void testFloatAlwaysConstant();
  void testConstantMethod();
  void testCompareWithTwoConstantVariables();
  void testComplexConstantComparison();
  void testOnlyEvaluateTheNecessaryCondition();
  void testSamePointerAlwaysContant();
  void testSameValueDifferentPointerComparedByPointerIsNotConstant();
  void testSameValueDifferentPointerComparedByValueIsConstant();
};
