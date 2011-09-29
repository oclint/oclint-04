#include <cxxtest/TestSuite.h>
#include "mo/rule/CyclomaticComplexityRule.h"

class CyclomaticComplexityRuleTest : public CxxTest::TestSuite { 
private:
  CyclomaticComplexityRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testCCNNineIsNotASmell();
  void testCCNTenIsASmell();
  void testCCNElevenIsASmell();
};
