#include <cxxtest/TestSuite.h>
#include "mo/rule/ConstantIfStatementRule.h"

class ConstantIfStatementRuleTest : public CxxTest::TestSuite { 
private:
  ConstantIfStatementRule *_rule;
  
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testGoodConditionExpression();
  void testCompareTwoKnownBoolValuesAlwaysBeTrue();
  void testCompareTwoKnownBoolValuesAlwaysBeFalse();
};
