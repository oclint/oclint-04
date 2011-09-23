#include "mo/rule/UnusedFormalParameterRuleTest.h"
#include "mo/util/TestCursorUtil.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"

void UnusedFormalParameterRuleTest::setUp() {
  _rule = new UnusedFormalParameterRule();
}

void UnusedFormalParameterRuleTest::tearDown() {
  delete _rule;
}

void UnusedFormalParameterRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "unused formal parameter");
}

void UnusedFormalParameterRuleTest::testMethodWithUsedParameter() {
  StringSourceCode strCode("int aMethod(int a) { a++; return 0; }", "m");
  CXCursor paramVarDeclCursor = TestCursorUtil::getVarDeclCursor(strCode);
  ViolationSet violationSet;
  _rule->apply(paramVarDeclCursor, paramVarDeclCursor, violationSet);
  TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
}

void UnusedFormalParameterRuleTest::testMethodWithUnusedParameter() {
  StringSourceCode strCode("int aMethod(int a) { return 0; }", "m");
  CXCursor paramVarDeclCursor = TestCursorUtil::getVarDeclCursor(strCode);
  ViolationSet violationSet;
  _rule->apply(paramVarDeclCursor, paramVarDeclCursor, violationSet);
  TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
  Violation violation = violationSet.getViolations().at(0);
  TS_ASSERT_EQUALS(violation.rule, _rule);
}

void UnusedFormalParameterRuleTest::testObjCMethodWithUnusedParameter() {
  StringSourceCode strCode("@interface AClass\n@end\n\
    @implementation AClass\n- (void)aMethod:(int)a {}\n@end", "m");
  CXCursor paramVarDeclCursor = TestCursorUtil::getVarDeclCursor(strCode);
  ViolationSet violationSet;
  _rule->apply(paramVarDeclCursor, paramVarDeclCursor, violationSet);
  TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
  Violation violation = violationSet.getViolations().at(0);
  TS_ASSERT_EQUALS(violation.rule, _rule);
}

void UnusedFormalParameterRuleTest::testObjCMethodDeclarationInsideInterface() {
  StringSourceCode strCode("@interface AnInterface\n- (void)aMethod:(int)a;\n@end", "m");
  CXCursor paramVarDeclCursor = TestCursorUtil::getVarDeclCursor(strCode);
  ViolationSet violationSet;
  _rule->apply(paramVarDeclCursor, paramVarDeclCursor, violationSet);
  TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
}

void UnusedFormalParameterRuleTest::testUsedLocalVariable() {
  StringSourceCode strCode("int aMethod() { int a; a = 1; return 0; }", "m");
  CXCursor paramVarDeclCursor = TestCursorUtil::getVarDeclCursor(strCode);
  ViolationSet violationSet;
  _rule->apply(paramVarDeclCursor, paramVarDeclCursor, violationSet);
  TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
}

void UnusedFormalParameterRuleTest::testUnusedLocalVariable() {
  StringSourceCode strCode("int aMethod() { int a; return 0; }", "m");
  CXCursor paramVarDeclCursor = TestCursorUtil::getVarDeclCursor(strCode);
  ViolationSet violationSet;
  _rule->apply(paramVarDeclCursor, paramVarDeclCursor, violationSet);
  TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
  Violation violation = violationSet.getViolations().at(0);
  TS_ASSERT_EQUALS(violation.rule, _rule);
}

void UnusedFormalParameterRuleTest::testUnusedLocalVariableWithIntialAssignment() {
  StringSourceCode strCode("int aMethod() { int a = 1; return 0; }", "m");
  CXCursor paramVarDeclCursor = TestCursorUtil::getVarDeclCursor(strCode);
  ViolationSet violationSet;
  _rule->apply(paramVarDeclCursor, paramVarDeclCursor, violationSet);
  TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
  Violation violation = violationSet.getViolations().at(0);
  TS_ASSERT_EQUALS(violation.rule, _rule);
}
