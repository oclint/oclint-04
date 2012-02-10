#include <cxxtest/TestSuite.h>
#include "oclint/rule/CyclomaticComplexityRule.h"

class CyclomaticComplexityRuleTest : public CxxTest::TestSuite { 
private:
  CyclomaticComplexityRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated, string description);
  void checkRule(string source, bool isViolated, string description);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testCCNSevenIsNotASmell();
  void testCCNEightIsASmell();
  void testCCNNineIsASmell();
};
