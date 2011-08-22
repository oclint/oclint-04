#include <cxxtest/TestSuite.h>
#include "mo/rule/EmptyIfStatementRule.h"

class EmptyIfStatementRuleTest : public CxxTest::TestSuite { 
private:
  EmptyIfStatementRule *_rule;
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testGoodIfStatement();
  void testIfStatementWithEmptyComponent();
  void testIfStatementWithNull();
};
