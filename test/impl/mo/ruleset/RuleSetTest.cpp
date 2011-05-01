#include "mo/ruleset/RuleSetTest.h"
#include "mo/rule/MockRule.h"

void RuleSetTest::testMockRuleBePushed() {
  TS_ASSERT_EQUALS(RuleSet::numberOfRules(), 1);
}
