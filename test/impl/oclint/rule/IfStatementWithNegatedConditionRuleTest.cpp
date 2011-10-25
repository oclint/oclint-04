#include "oclint/rule/IfStatementWithNegatedConditionRuleTest.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/StringSourceCode.h"
#include "oclint/util/CursorUtil.h"
#include "oclint/util/CursorExtractionUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

void IfStatementWithNegatedConditionRuleTest::setUp() {
  _rule = new IfStatementWithNegatedConditionRule();
}

void IfStatementWithNegatedConditionRuleTest::tearDown() {
  delete _rule;
}

void IfStatementWithNegatedConditionRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "if statement with negated condition");
}

void IfStatementWithNegatedConditionRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated) {
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

void IfStatementWithNegatedConditionRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorUtil::getStmt(node);
    return stmt && isa<IfStmt>(stmt);
  });
  checkRule(cursorPair, isViolated);
}

void IfStatementWithNegatedConditionRuleTest::testSimpleIfStatement() {
  checkRule("bool aMethod() { if (1) {;} return true; }", false);
}

void IfStatementWithNegatedConditionRuleTest::testNegativeConditionWithoutElseBlock() {
  checkRule("bool aMethod() { if (!1) {;} return true; }", false);
}

void IfStatementWithNegatedConditionRuleTest::testNegativeConditionWithElseBlockWithContent() {
  checkRule("bool aMethod() { if (!1) {;} else {;} return true; }", true);
}

void IfStatementWithNegatedConditionRuleTest::testNegativeComprisonBetweenTwoValues() {
  checkRule("bool aMethod() { if (1 != 0) {;} else {;} return true; }", true);
}
