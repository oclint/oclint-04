#include "mo/rule/UnusedLocalVariableRuleTest.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/CursorExtractionUtil.h"

#include <clang/AST/Decl.h>

using namespace clang;

void UnusedLocalVariableRuleTest::setUp() {
  _rule = new UnusedLocalVariableRule();
}

void UnusedLocalVariableRuleTest::tearDown() {
  delete _rule;
}

void UnusedLocalVariableRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "unused local variable");
}

void UnusedLocalVariableRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated) {
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

void UnusedLocalVariableRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  });
  checkRule(cursorPair, isViolated);
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

void UnusedLocalVariableRuleTest::testDeclarationOutsideMethodShouldBeIgnored() {
  checkRule("int i = 1;", false);
}

void UnusedLocalVariableRuleTest::testUnusedMethodParameterShouldBeIgnoredInThisRule() {
  checkRule("int aMethod(int a) { return 0; }", false);
}
