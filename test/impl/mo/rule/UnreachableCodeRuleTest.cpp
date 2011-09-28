#include "mo/rule/UnreachableCodeRuleTest.h"
#include "mo/util/TestCursorUtil.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"

void UnreachableCodeRuleTest::setUp() {
  _rule = new UnreachableCodeRule();
}

void UnreachableCodeRuleTest::tearDown() {
  delete _rule;
}

void UnreachableCodeRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "unreachable code");
}

void UnreachableCodeRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  CXCursor compoundStmtCursor = TestCursorUtil::getCompoundStmtCursor(strCode);
  ViolationSet violationSet;
  _rule->apply(compoundStmtCursor, compoundStmtCursor, violationSet);
  if (isViolated) {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
    Violation violation = violationSet.getViolations().at(0);
    TS_ASSERT_EQUALS(violation.rule, _rule);
  }
  else {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
  }
}

void UnreachableCodeRuleTest::testGoodCompoundStmtWithoutReturnStmt() {
  checkRule("void aMethod() { int a; a = 1; a = 2; }", false);
}

void UnreachableCodeRuleTest::testGoodCompoundStmtWithReturnStmtAtLastLine() {
  checkRule("int aMethod() { int i = 1; return i; }", false);
}

void UnreachableCodeRuleTest::testUnreachableCodeAfterReturnStatement() {
  checkRule("int aMethod() { return 1; int i = 1; i++; }", true);
}

void UnreachableCodeRuleTest::testUnreachableCodeAfterBreakStatement() {
  StringSourceCode strCode("int aMethod() { for(;;) { break; int i = 1; i++; } }", "m");
  CXCursor compoundStmtCursor = TestCursorUtil::getForStmtContainingCompoundStmtCursor(strCode);
  ViolationSet violationSet;
  _rule->apply(compoundStmtCursor, compoundStmtCursor, violationSet);  
  TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
  Violation violation = violationSet.getViolations().at(0);
  TS_ASSERT_EQUALS(violation.rule, _rule);
}
