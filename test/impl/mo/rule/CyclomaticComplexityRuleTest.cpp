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

void CyclomaticComplexityRuleTest::testCCNNineIsNotASmell() {
  StringSourceCode strCode("@implementation ClassName\n- (void)aMethodWithNineCCN { \
    if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} }\n@end", "m");
  CXCursor methodDeclCursor = TestCursorUtil::getObjCMethodDecl(strCode);
  ViolationSet violationSet;
  _rule->apply(methodDeclCursor, methodDeclCursor, violationSet);
  TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
}

void CyclomaticComplexityRuleTest::testCCNTenIsASmell() {
  StringSourceCode strCode("@implementation ClassName\n- (void)aMethodWithTenCCN { \
    if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} }\n@end", "m");
  CXCursor methodDeclCursor = TestCursorUtil::getObjCMethodDecl(strCode);
  ViolationSet violationSet;
  _rule->apply(methodDeclCursor, methodDeclCursor, violationSet);
  TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
  Violation violation = violationSet.getViolations().at(0);
  TS_ASSERT_EQUALS(violation.rule, _rule);
}

void CyclomaticComplexityRuleTest::testCCNElevenIsASmell() {
  StringSourceCode strCode("@implementation ClassName\n- (void)aMethodWithTenCCN { \
    if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} if(1) {} }\n@end", "m");
  CXCursor methodDeclCursor = TestCursorUtil::getObjCMethodDecl(strCode);
  ViolationSet violationSet;
  _rule->apply(methodDeclCursor, methodDeclCursor, violationSet);
  TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
  Violation violation = violationSet.getViolations().at(0);
  TS_ASSERT_EQUALS(violation.rule, _rule);
}
