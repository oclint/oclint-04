#include "mo/rule/LongMethodRuleTest.h"
#include "mo/util/TestCursorUtil.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"

void LongMethodRuleTest::setUp() {
  _rule = new LongMethodRule();
}

void LongMethodRuleTest::tearDown() {
  delete _rule;
}

void LongMethodRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "long method");
}

void LongMethodRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  CXCursor methodDeclCursor = TestCursorUtil::getObjCMethodDecl(strCode);
  ViolationSet violationSet;
  _rule->apply(methodDeclCursor, methodDeclCursor, violationSet);
  if (isViolated) {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
    Violation violation = violationSet.getViolations().at(0);
    TS_ASSERT_EQUALS(violation.rule, _rule);
  }
  else {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
  }
}

void LongMethodRuleTest::testMethodWithSixStatementsIsNotASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithFiveStatements { \
    if(1) {} if(2) {} if(3) {} if(4) {} if(5) {} if(6) {} }\n@end";
  checkRule(strSource, false);
}

void LongMethodRuleTest::testMethodWithSevenStatementsIsASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithFiveStatements { \
    if(1) {} if(2) {} if(3) {} if(4) {} if(5) {} if(6) {} if(7) {} }\n@end";
  checkRule(strSource, true);
}

void LongMethodRuleTest::testmethodWithEightStatemetnsIsASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithFiveStatements { \
    if(1) {} if(2) {} if(3) {} if(4) {} if(5) {} if(6) {} if(7) {} if(8) {} }\n@end";
  checkRule(strSource, true);
}

void LongMethodRuleTest::testMethodWithNestedStatementsShouldNotBeCounted() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithFiveStatements { \
    if(1) { if(0) {} } if(2) { if(0) {} } if(3) { if(0) {} } if(4) {} if(5) {} if(6) {} }\n@end";
  checkRule(strSource, false);
}
