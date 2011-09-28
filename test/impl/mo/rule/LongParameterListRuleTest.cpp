#include "mo/rule/LongParameterListRuleTest.h"
#include "mo/util/TestCursorUtil.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"

void LongParameterListRuleTest::setUp() {
  _rule = new LongParameterListRule();
}

void LongParameterListRuleTest::tearDown() {
  delete _rule;
}

void LongParameterListRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "long parameter list");
}

void LongParameterListRuleTest::checkRule(string source, string sourcetype, bool isViolated) {
  StringSourceCode strCode(source, sourcetype);
  CXCursor methodDeclCursor;
  if (sourcetype == "m") {
    methodDeclCursor = TestCursorUtil::getObjCMethodDeclCursor(strCode);
  }
  else {
    methodDeclCursor = TestCursorUtil::getFunctionDeclCursor(strCode);
  }
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

void LongParameterListRuleTest::testObjCMethodWithThreeParametersIsNotASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithThreeParameters:(int)param1 param2:(int)param2 param3:(int)param3 {}\n@end";
  checkRule(strSource, "m", false);
}

void LongParameterListRuleTest::testObjCMethodWithFourParametersIsASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithThreeParameters:(int)param1 param2:(int)param2 param3:(int)param3 param4:(int)param4 {}\n@end";
  checkRule(strSource, "m", true);
}

void LongParameterListRuleTest::testObjCMethodWithFiveParametersIsASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithThreeParameters:(int)param1 param2:(int)param2 param3:(int)param3 param4:(int)param4 param5:... {}\n@end";
  checkRule(strSource, "m", true);
}

void LongParameterListRuleTest::testCppMethodWithThreeParametersIsNotASmell() {
  string strSource = "int aMethod(int a, int b, int c) {}";
  checkRule(strSource, "cpp", false);
}

void LongParameterListRuleTest::testCppMethodWithFourParametersIsASmell() {
  string strSource = "int aMethod(int a, int b, int c, int d) {}";
  checkRule(strSource, "cpp", true);
}

void LongParameterListRuleTest::testCppMethodWithFiveParametersIsASmell() {
  string strSource = "int aMethod(int a, int b, int c, int d, int e) {}";
  checkRule(strSource, "cpp", true);
}
