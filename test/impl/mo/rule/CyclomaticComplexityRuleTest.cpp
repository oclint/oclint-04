#include "mo/rule/CyclomaticComplexityRuleTest.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/CursorExtractionUtil.h"

#include <clang/AST/DeclObjC.h>

using namespace clang;

void CyclomaticComplexityRuleTest::setUp() {
  _rule = new CyclomaticComplexityRule();
}

void CyclomaticComplexityRuleTest::tearDown() {
  delete _rule;
}

void CyclomaticComplexityRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "high cyclomatic complexity");
}

void CyclomaticComplexityRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated) {
  ViolationSet violationSet;
  _rule->apply(cursorPair.first, cursorPair.second, violationSet);
  if (isViolated) {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
    Violation violation = violationSet.getViolations().at(0);
    TS_ASSERT_EQUALS(violation.rule, _rule);
  }
  else {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
  }
}

void CyclomaticComplexityRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  });
  checkRule(cursorPair, isViolated);
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
