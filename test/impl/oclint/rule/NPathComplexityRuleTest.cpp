#include "oclint/rule/NPathComplexityRuleTest.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/StringSourceCode.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/CursorExtractionHelper.h"

#include <clang/AST/DeclObjC.h>

using namespace clang;

void NPathComplexityRuleTest::setUp() {
  _rule = new NPathComplexityRule();
}

void NPathComplexityRuleTest::tearDown() {
  delete _rule;
}

void NPathComplexityRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "high npath complexity");
}

void NPathComplexityRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated, string description) {
  ViolationSet violationSet;
  _rule->apply(cursorPair.first, cursorPair.second, violationSet);
  if (isViolated) {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
    Violation violation = violationSet.getViolations().at(0);
    TS_ASSERT_EQUALS(violation.rule, _rule);
    TS_ASSERT_EQUALS(violation.description, description);
  }
  else {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
  }
}

void NPathComplexityRuleTest::checkRule(string source, bool isViolated, string description) {
  StringSourceCode strCode(source, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<ObjCMethodDecl>(decl);
  });
  checkRule(cursorPair, isViolated, description);
}

void NPathComplexityRuleTest::testNPathEightIsNotASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithEightNPath { \
    if(1) {} if(1) {} if(1) {} }\n@end";
  checkRule(strSource, false, "");
}

void NPathComplexityRuleTest::testNPathTwoHunhredAndFiftySixIsASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithTwoHunhredAndFiftySixNPath { \
    if(1) {} if(2) {} if(3) {} if(4) {} if(5) {} if(6) {} if(7) {} if(8) {} }\n@end";
  checkRule(strSource, true, "NPath Complexity Number 256 exceeds limit of 200.");
}
