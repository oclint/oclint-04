#include <cxxtest/TestSuite.h>
#include "oclint/rule/NPathComplexityRule.h"

class NPathComplexityRuleTest : public CxxTest::TestSuite {
private:
  NPathComplexityRule *_rule;

  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated, string description);
  void checkRule(string source, bool isViolated, string description);

public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testNPathEightIsNotASmell();
  void testNPathTwoHunhredAndFiftySixIsASmell();
};
