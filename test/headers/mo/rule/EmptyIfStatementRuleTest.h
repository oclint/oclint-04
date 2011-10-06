#include <cxxtest/TestSuite.h>
#include "mo/rule/EmptyIfStatementRule.h"

class EmptyIfStatementRuleTest : public CxxTest::TestSuite { 
private:
  EmptyIfStatementRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testGoodIfStatement();
  void testIfStatementWithEmptyComponent();
  void testIfStatementWithNull();
  void testIfStatementWithEmptyElseComponent();
  void testIfStatementWithNullElseComponent();
};
