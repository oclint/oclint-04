#include "mo/exception/MOException.h"
#include "mo/RuleViolationTest.h"

void RuleViolationTest::setUp() {
  violation = new RuleViolation();
}

void RuleViolationTest::tearDown() {
  delete violation;
}

void RuleViolationTest::testNoViolation() {
  TS_ASSERT_EQUALS(violation->numberOfViolations(), 0);
}

void RuleViolationTest::testAddViolation() {
  violation->addViolation("test violation");
  TS_ASSERT_EQUALS(violation->numberOfViolations(), 1);
  TS_ASSERT_EQUALS(violation->violationAt(0), "test violation");
}

void RuleViolationTest::testGetViolationOutOfRangeWithNoViolation() {
  try {
    violation->violationAt(0);
    TS_FAIL("no violation when getting violation");
  } catch (MOException *ex) {
    //
  }
}

void RuleViolationTest::testGetViolationOutOfRangeWithNegativeIndex() {
  try {
    violation->violationAt(-1);
    TS_FAIL("negative index when getting violation");
  } catch (MOException *ex) {
    //
  }
}

void RuleViolationTest::testGetViolationOutOfRangeWithIndexOverNumberOfViolations() {
  violation->addViolation("test violation");
  try {
    violation->violationAt(1);
    TS_FAIL("index over number of violations when getting violation");
  } catch (MOException *ex) {
    //
  }
}
