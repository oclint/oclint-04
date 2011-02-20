#include "mo/exception/MOException.h"
#include "mo/RuleViolation.h"
#include "mo/RuleDataTest.h"
#include "mo/rule/MockRule.h"

void RuleDataTest::setUp() {
  data = new RuleData();
}

void RuleDataTest::tearDown() {
  delete data;
}

void RuleDataTest::testNoViolation() {
  TS_ASSERT_EQUALS(data->numberOfViolations(), 0);
}

void RuleDataTest::testAddViolation() {
  RuleViolation violation(clang_getNullCursor(), new MockRule());
  data->addViolation(violation);
  TS_ASSERT_EQUALS(data->numberOfViolations(), 1);
  TS_ASSERT(clang_equalCursors(data->violationAt(0).cursor, clang_getNullCursor()));
}

void RuleDataTest::testGetViolationOutOfRangeWithNoViolation() {
  try {
    data->violationAt(0);
    TS_FAIL("no violation when getting violation");
  } catch (MOException& ex) {
    //
  }
}

void RuleDataTest::testGetViolationOutOfRangeWithNegativeIndex() {
  try {
    data->violationAt(-1);
    TS_FAIL("negative index when getting violation");
  } catch (MOException& ex) {
    //
  }
}

void RuleDataTest::testGetViolationOutOfRangeWithIndexOverNumberOfViolations() {
  RuleViolation violation(clang_getNullCursor(), new MockRule());
  data->addViolation(violation);
  try {
    data->violationAt(1);
    TS_FAIL("index over number of violations when getting violation");
  } catch (MOException& ex) {
    //
  }
}
