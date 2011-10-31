#include "oclint/rule/EmptyIfStatementRuleTest.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/StringSourceCode.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/CursorExtractionHelper.h"

#include <clang/AST/Stmt.h>

using namespace clang;

void EmptyIfStatementRuleTest::setUp() {
  _rule = new EmptyIfStatementRule();
}

void EmptyIfStatementRuleTest::tearDown() {
  delete _rule;
}

void EmptyIfStatementRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "empty if statement");
}

void EmptyIfStatementRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated) {
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

void EmptyIfStatementRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorHelper::getStmt(node);
    return stmt && isa<IfStmt>(stmt);
  });
  checkRule(cursorPair, isViolated);
}

void EmptyIfStatementRuleTest::testGoodIfStatement() {
  checkRule("int main() { if (1) {;} return 0; }", false);
}

void EmptyIfStatementRuleTest::testIfStatementWithEmptyComponent() {
  checkRule("int main() { if (1) {} return 0; }", true);
}

void EmptyIfStatementRuleTest::testIfStatementWithNull() {
  checkRule("int main() { if (1); return 0; }", true);
}

void EmptyIfStatementRuleTest::testIfStatementWithEmptyElseComponent() {
  checkRule("int main() { if (1) {;} else {} return 0; }", true);
}

void EmptyIfStatementRuleTest::testIfStatementWithNullElseComponent() {
  checkRule("int main() { if (1) {;} else; return 0; }", true);
}
