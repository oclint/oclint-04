#include "mo/rule/EmptyIfStatementRuleTest.h"
#include "mo/util/TestCursorUtil.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"

void EmptyIfStatementRuleTest::setUp() {
  _rule = new EmptyIfStatementRule();
}

void EmptyIfStatementRuleTest::tearDown() {
  delete _rule;
}

void EmptyIfStatementRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "empty if statement");
}

void EmptyIfStatementRuleTest::checkRule(string source, bool isViolated) {
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

void EmptyIfStatementRuleTest::testGoodIfStatement() {
  checkRule("int main() { if (1) {;} return 0; }", false);
}

void EmptyIfStatementRuleTest::testIfStatementWithEmptyComponent() {
  checkRule("int main() { if (1) {} return 0; }", true);
}

void EmptyIfStatementRuleTest::testIfStatementWithNull() {
  checkRule("int main() { if (1); return 0; }", true);
}
