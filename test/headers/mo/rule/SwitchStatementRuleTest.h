#include <cxxtest/TestSuite.h>
#include "mo/rule/SwitchStatementRule.h"

class SwitchStatementRuleTest : public CxxTest::TestSuite { 
private:
  SwitchStatementRule *rule;
  
public:
  void setUp();
  void tearDown();
  void testApply();
  void testName();
};
