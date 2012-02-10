#include "oclint/exception/GenericException.h"
#include "oclint/Violation.h"
#include "oclint/ViolationSetTest.h"
#include "oclint/rule/MockRule.h"

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
  Violation violation(clang_getNullCursor(), new MockRule());
  _violationSet->addViolation(violation);
  TS_ASSERT_EQUALS(_violationSet->numberOfViolations(), 1);
}

void ViolationSetTest::testGetViolations() {
  Violation violation(clang_getNullCursor(), new MockRule(), "violation description");
  _violationSet->addViolation(violation);
  const vector<Violation> violations = _violationSet->getViolations();
  TS_ASSERT(clang_equalCursors(violations.at(0).cursor, clang_getNullCursor()));
  TS_ASSERT_EQUALS(violations.at(0).description, "violation description");
}

void ViolationSetTest::testAddViolationWithAttributes() {
  _violationSet->addViolation(clang_getNullCursor(), new MockRule(), "violation description");
  const vector<Violation> violations = _violationSet->getViolations();
  TS_ASSERT(clang_equalCursors(violations.at(0).cursor, clang_getNullCursor()));
  TS_ASSERT_EQUALS(violations.at(0).description, "violation description");
}
