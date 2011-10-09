#include "mo/rule/RedundantLocalVariableRuleTest.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/CursorExtractionUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

void RedundantLocalVariableRuleTest::setUp() {
  _rule = new RedundantLocalVariableRule();
}

void RedundantLocalVariableRuleTest::tearDown() {
  delete _rule;
}

void RedundantLocalVariableRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "redundant local variable");
}

void RedundantLocalVariableRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated) {
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

void RedundantLocalVariableRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorUtil::getStmt(node);
    Stmt *parentStmt = CursorUtil::getStmt(parentNode);
    return stmt && parentStmt && isa<ReturnStmt>(stmt) && isa<CompoundStmt>(parentStmt);
  });
  checkRule(cursorPair, isViolated);
}

void RedundantLocalVariableRuleTest::testNoRedundantLocalVariable() {
  checkRule("int aMethod() { int i = 1; i++; return 0; }", false);
}

void RedundantLocalVariableRuleTest::testRedundantDeclarationVariableFollowedByReturnStmt() {
  checkRule("int aMethod() { int i = 1; return i; }", true);
}

void RedundantLocalVariableRuleTest::testRedundantDeclarationVariableFollowedByReturnStmtInANestedCompoundStmt() {
  checkRule("int aMethod() { if (1) { int i = 1; return i; } return 0; }", true);
}
