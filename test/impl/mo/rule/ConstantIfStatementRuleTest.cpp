#include "mo/rule/ConstantIfStatementRuleTest.h"
#include "mo/util/TestCursorUtil.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"

void ConstantIfStatementRuleTest::setUp() {
  _rule = new ConstantIfStatementRule();
}

void ConstantIfStatementRuleTest::tearDown() {
  delete _rule;
}

void ConstantIfStatementRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "constant if statement");
}

void ConstantIfStatementRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  CXCursor ifStmtCursor = TestCursorUtil::getIfStmtCursor(strCode);
  ViolationSet violationSet;
  _rule->apply(ifStmtCursor, ifStmtCursor, violationSet);
  if (isViolated) {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
    Violation violation = violationSet.getViolations().at(0);
    TS_ASSERT_EQUALS(violation.rule, _rule);
  }
  else {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
  }
}

void ConstantIfStatementRuleTest::testGoodConditionExpression() {
  checkRule("void aMethod(int b, int c) { if (b == c) {;} }", false);
}

void ConstantIfStatementRuleTest::testCompareTwoKnownBoolValuesAlwaysBeTrue() {
  checkRule("int main() { if (1 == 1) {;} return 0; }", true);
}

void ConstantIfStatementRuleTest::testCompareTwoKnownBoolValuesAlwaysBeFalse() {
  checkRule("int main() { if (1 == 0) {;} return 0; }", true);
}
