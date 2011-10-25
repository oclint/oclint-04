#include <cxxtest/TestSuite.h>
#include "oclint/rule/NPathComplexityRule.h"

class NPathComplexityRuleTest : public CxxTest::TestSuite { 
private:
  NPathComplexityRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testNPathEightIsNotASmell();
  void testNPathTwoHunhredAndFiftySixIsASmell();
};
