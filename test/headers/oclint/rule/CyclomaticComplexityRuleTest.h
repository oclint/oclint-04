#include <cxxtest/TestSuite.h>
#include "oclint/rule/CyclomaticComplexityRule.h"

class CyclomaticComplexityRuleTest : public CxxTest::TestSuite { 
private:
  CyclomaticComplexityRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testCCNSevenIsNotASmell();
  void testCCNEightIsASmell();
  void testCCNNineIsASmell();
};
