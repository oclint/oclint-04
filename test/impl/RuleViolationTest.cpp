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
  violation->addViolation("");
  TS_ASSERT_EQUALS(violation->numberOfViolations(), 1);
}
