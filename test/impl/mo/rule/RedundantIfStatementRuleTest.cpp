#include "mo/rule/RedundantIfStatementRuleTest.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/CursorExtractionUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

void RedundantIfStatementRuleTest::setUp() {
  _rule = new RedundantIfStatementRule();
}

void RedundantIfStatementRuleTest::tearDown() {
  delete _rule;
}

void RedundantIfStatementRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "redundant if statement");
}

void RedundantIfStatementRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated) {
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

void RedundantIfStatementRuleTest::checkRule(string source, string sourceType, bool isViolated) {
  StringSourceCode strCode(source, sourceType);
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorUtil::getStmt(node);
    return stmt && isa<IfStmt>(stmt);
  }, -1);
  checkRule(cursorPair, isViolated);
}

void RedundantIfStatementRuleTest::testGoodIfStatement() {
  checkRule("int aMethod() { if (1) { ; } return 0; }", "m", false);
}

void RedundantIfStatementRuleTest::testIfStatementWithOneThenAndZeroElse() {
  checkRule("int aMethod() { if (1) { return 1; } else return 0; }", "c", true);
}

void RedundantIfStatementRuleTest::testIfStatementWithZeroThenAndOneElse() {
  checkRule("int aMethod() { if (1) return 0; else { return 1; } }", "c", true);
}

void RedundantIfStatementRuleTest::testIfStatementWithTrueThenAndFalseElse() {
  checkRule("bool aMethod() { if (1) { return true; } else return false; }", "cpp", true);
}

void RedundantIfStatementRuleTest::testIfStatementWithFalseThenAndTrueElse() {
  checkRule("bool aMethod() { if (1) return false; else { return true; } }", "cpp", true);
}

void RedundantIfStatementRuleTest::testIfStatementWithYesThenAndNoElse() {
  checkRule("#import <objc/objc.h> \n BOOL aMethod() { if (1) { return YES; } else return NO; }", "m", true);
}

void RedundantIfStatementRuleTest::testIfStatementWithNoThenAndYesElse() {
  checkRule("#import <objc/objc.h> \n BOOL aMethod() { if (1) return NO; else { return YES; } }", "m", true);
}
