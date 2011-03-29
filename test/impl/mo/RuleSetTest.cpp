#include "mo/RuleSetTest.h"
#include "mo/rule/MockRule.h"

void RuleSetTest::testMockRuleBePushed() {
  // Curently, there are two rules, one is SwitchStatementRule
  // the other is MockRule
  TS_ASSERT_EQUALS(RuleSet::numberOfRules(), 2);
}
