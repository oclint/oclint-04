#include "mo/rule/CyclomaticComplexityRuleTest.h"
#include "mo/util/TestCursorUtil.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"

void CyclomaticComplexityRuleTest::setUp() {
  _rule = new CyclomaticComplexityRule();
}

void CyclomaticComplexityRuleTest::tearDown() {
  delete _rule;
}

void CyclomaticComplexityRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "high cyclomatic complexity");
}

void CyclomaticComplexityRuleTest::checkRule(string source, bool isViolated) {
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

void CyclomaticComplexityRuleTest::testCCNNineIsNotASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithNineCCN { \
    if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} }\n@end";
  checkRule(strSource, false);
}

void CyclomaticComplexityRuleTest::testCCNTenIsASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithTenCCN { \
    if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} }\n@end";
  checkRule(strSource, true);
}

void CyclomaticComplexityRuleTest::testCCNElevenIsASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithTenCCN { \
    if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} }\n@end";
  checkRule(strSource, true);
}
