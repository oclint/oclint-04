#include "mo/rule/SwitchStatementRuleTest.h"
#include "mo/RuleData.h"
#include "mo/RuleViolation.h"
#include "mo/util/TestCursorUtil.h"

void SwitchStatementRuleTest::setUp() {
  _rule = new SwitchStatementRule();
}

void SwitchStatementRuleTest::tearDown() {
  delete _rule;
  _rule = NULL;
}

void SwitchStatementRuleTest::testApply() {
  RuleData data;
  CXCursor cursor = TestCursorUtil::getSwitchStmtCursor();
  _rule->apply(cursor, cursor, data);
  TS_ASSERT_EQUALS(data.numberOfViolations(), 1);
}

void SwitchStatementRuleTest::testName() {
  TS_ASSERT_EQUALS(_rule->name(), string("switch statement"));
}


