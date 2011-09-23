#include "mo/rule/UnusedLocalVariableRuleTest.h"
#include "mo/util/TestCursorUtil.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"

void UnusedLocalVariableRuleTest::setUp() {
  _rule = new UnusedLocalVariableRule();
}

void UnusedLocalVariableRuleTest::tearDown() {
  delete _rule;
}

void UnusedLocalVariableRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "unused local variable");
}

void UnusedLocalVariableRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  CXCursor varDeclCursor = TestCursorUtil::getVarDeclCursor(strCode);
  ViolationSet violationSet;
  _rule->apply(varDeclCursor, varDeclCursor, violationSet);
  if (isViolated) {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
    Violation violation = violationSet.getViolations().at(0);
    TS_ASSERT_EQUALS(violation.rule, _rule);
  }
  else {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
  }
}

void UnusedLocalVariableRuleTest::testMethodWithUsedParameter() {
  checkRule("int aMethod(int a) { a++; return 0; }", false);
}

void UnusedLocalVariableRuleTest::testMethodWithUnusedParameter() {
  checkRule("int aMethod(int a) { return 0; }", true);
}

void UnusedLocalVariableRuleTest::testObjCMethodWithUnusedParameter() {
  string strSource = "@interface AClass\n@end\n\
    @implementation AClass\n- (void)aMethod:(int)a {}\n@end";
    checkRule(strSource, true);
}

void UnusedLocalVariableRuleTest::testObjCMethodDeclarationInsideInterface() {
  checkRule("@interface AnInterface\n- (void)aMethod:(int)a;\n@end", false);
}

void UnusedLocalVariableRuleTest::testUsedLocalVariable() {
  checkRule("int aMethod() { int a; a = 1; return 0; }", false);
}

void UnusedLocalVariableRuleTest::testUnusedLocalVariable() {
  checkRule("int aMethod() { int a; return 0; }", true);
}

void UnusedLocalVariableRuleTest::testUnusedLocalVariableWithIntialAssignment() {
  checkRule("int aMethod() { int a = 1; return 0; }", true);
}
