#include "mo/exception/MOException.h"
#include "mo/RuleViolation.h"
#include "mo/RuleDataTest.h"
#include "mo/rule/MockRule.h"

void RuleDataTest::setUp() {
  _data = new RuleData();
}

void RuleDataTest::tearDown() {
  delete _data;
  _data = NULL;
}

void RuleDataTest::testNoRule() {
  TS_ASSERT_EQUALS(_data->numberOfRules(), 0);
}

void RuleDataTest::testAddRule() {
  _data->addRule(new MockRule());
  TS_ASSERT_EQUALS(_data->numberOfRules(), 1);
  TS_ASSERT_EQUALS(_data->ruleAt(0)->name(), "mock rule");
}

void RuleDataTest::testGetRuleOutOfRangeWithNoRule() {
  try {
    _data->ruleAt(0);
    TS_FAIL("no rule when getting rule");
  } catch (MOException& ex) {
    //
  }
}

void RuleDataTest::testGetRuleOutOfRangeWithNegativeIndex() {
  try {
    _data->ruleAt(-1);
    TS_FAIL("negative index when getting rule");
  } catch (MOException& ex) {
    //
  }
}

void RuleDataTest::testGetRuleOutOfRangeWithIndexOverNumberOfRules() {
  _data->addRule(new MockRule());
  try {
    _data->ruleAt(1);
    TS_FAIL("index over number of rules when getting rule");
  } catch (MOException& ex) {
    //
  }
}

void RuleDataTest::testNoViolation() {
  TS_ASSERT_EQUALS(_data->numberOfViolations(), 0);
}

void RuleDataTest::testAddViolation() {
  RuleViolation violation(clang_getNullCursor(), new MockRule());
  _data->addViolation(violation);
  TS_ASSERT_EQUALS(_data->numberOfViolations(), 1);
}

void RuleDataTest::testGetViolations() {
  RuleViolation violation(clang_getNullCursor(), new MockRule());
  _data->addViolation(violation);
  const vector<RuleViolation> violations = _data->getViolations();
  TS_ASSERT(clang_equalCursors(violations.at(0).cursor, clang_getNullCursor()));
}
