#include <cxxtest/TestSuite.h>
#include "mo/rule/SwitchStatementRule.h"

class SwitchStatementRuleTest : public CxxTest::TestSuite { 
private:
  SwitchStatementRule *_rule;
  
public:
  void setUp();
  void tearDown();
  void testApply();
  void testName();
};
