#include <cxxtest/TestSuite.h>
#include "mo/rule/LongParameterListRule.h"

class LongParameterListRuleTest : public CxxTest::TestSuite { 
private:
  LongParameterListRule *_rule;
  
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testMethodWithThreeParametersIsNotASmell();
  void testMethodWithFourParametersIsASmell();
  void testMethodWithFiveParametersIsASmell();
};
