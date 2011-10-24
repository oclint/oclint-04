#include "oclint/RuleSetTest.h"
#include "oclint/rule/MockRule.h"

void RuleSetTest::testMockRuleBePushed() {
  TS_ASSERT_EQUALS(RuleSet::numberOfRules(), 13);
  // TODO: there should be a way to automatically update this value
}
