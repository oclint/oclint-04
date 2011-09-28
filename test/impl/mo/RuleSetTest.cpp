#include "mo/RuleSetTest.h"
#include "mo/rule/MockRule.h"

void RuleSetTest::testMockRuleBePushed() {
  TS_ASSERT_EQUALS(RuleSet::numberOfRules(), 8);
  // TODO: there should be a way to automatically update this value
}
