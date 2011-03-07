#include "mo/rule/SwitchStatementRuleTest.h"
#include "mo/RuleData.h"
#include "mo/RuleViolation.h"
#include "mo/util/TestCursorUtil.h"

void SwitchStatementRuleTest::setUp() {
  rule = new SwitchStatementRule();
}

void SwitchStatementRuleTest::tearDown() {
  delete rule;
}

void SwitchStatementRuleTest::testApply() {
  RuleData data;
  CXCursor cursor = TestCursorUtil::getSwitchStmtCursor();
  rule->apply(cursor, cursor, data);
  TS_ASSERT_EQUALS(data.numberOfViolations(), 1);
}

void SwitchStatementRuleTest::testName() {
  TS_ASSERT_EQUALS(rule->name(), string("switch statement"));
}


