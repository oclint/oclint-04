#include "mo/exception/MOException.h"
#include "mo/RuleViolation.h"
#include "mo/ViolationSetTest.h"
#include "mo/rule/MockRule.h"

void ViolationSetTest::setUp() {
  _violationSet = new ViolationSet();
}

void ViolationSetTest::tearDown() {
  delete _violationSet;
}

void ViolationSetTest::testNoViolation() {
  TS_ASSERT_EQUALS(_violationSet->numberOfViolations(), 0);
}

void ViolationSetTest::testAddViolation() {
  RuleViolation violation(clang_getNullCursor(), new MockRule());
  _violationSet->addViolation(violation);
  TS_ASSERT_EQUALS(_violationSet->numberOfViolations(), 1);
}

void ViolationSetTest::testGetViolations() {
  RuleViolation violation(clang_getNullCursor(), new MockRule());
  _violationSet->addViolation(violation);
  const vector<RuleViolation> violations = _violationSet->getViolations();
  TS_ASSERT(clang_equalCursors(violations.at(0).cursor, clang_getNullCursor()));
}
