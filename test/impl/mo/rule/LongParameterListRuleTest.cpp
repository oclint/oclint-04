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

void LongParameterListRuleTest::checkRule(string source, bool isViolated) {
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

void LongParameterListRuleTest::testMethodWithThreeParametersIsNotASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithThreeParameters:(int)param1 param2:(int)param2 param3:(int)param3 {}\n@end";
  checkRule(strSource, false);
}

void LongParameterListRuleTest::testMethodWithFourParametersIsASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithThreeParameters:(int)param1 param2:(int)param2 param3:(int)param3 param4:(int)param4 {}\n@end";
  checkRule(strSource, true);
}

void LongParameterListRuleTest::testMethodWithFiveParametersIsASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithThreeParameters:(int)param1 param2:(int)param2 param3:(int)param3 param4:(int)param4 param5:... {}\n@end";
  checkRule(strSource, true);
}
