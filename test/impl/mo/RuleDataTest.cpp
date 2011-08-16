#include "mo/exception/MOException.h"
#include "mo/RuleViolation.h"
#include "mo/RuleDataTest.h"
#include "mo/rule/MockRule.h"

void RuleDataTest::setUp() {
  _data = new RuleData();
}

void RuleDataTest::tearDown() {
  delete _data;
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
