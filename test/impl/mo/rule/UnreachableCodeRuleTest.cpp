#include "mo/rule/UnreachableCodeRuleTest.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/CursorExtractionUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

void UnreachableCodeRuleTest::setUp() {
  _rule = new UnreachableCodeRule();
}

void UnreachableCodeRuleTest::tearDown() {
  delete _rule;
}

void UnreachableCodeRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "unreachable code");
}

void UnreachableCodeRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated) {
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

void UnreachableCodeRuleTest::checkRuleOnFunctionRootComponent(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorUtil::getStmt(node);
    return stmt && isa<CompoundStmt>(stmt);
  });
  checkRule(cursorPair, isViolated);
}

void UnreachableCodeRuleTest::testGoodCompoundStmtWithoutReturnStmt() {
  checkRuleOnFunctionRootComponent("void aMethod() { int a; a = 1; a = 2; }", false);
}

void UnreachableCodeRuleTest::testGoodCompoundStmtWithReturnStmtAtLastLine() {
  checkRuleOnFunctionRootComponent("int aMethod() { int i = 1; return i; }", false);
}

void UnreachableCodeRuleTest::testUnreachableCodeAfterReturnStatement() {
  checkRuleOnFunctionRootComponent("int aMethod() { return 1; int i = 1; i++; }", true);
}

void UnreachableCodeRuleTest::testUnreachableCodeAfterBreakStatement() {
  StringSourceCode strCode("int aMethod() { for(;;) { break; int i = 1; i++; } }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorUtil::getStmt(node);
    Stmt *parentStmt = CursorUtil::getStmt(parentNode);
    return stmt && parentStmt && isa<CompoundStmt>(stmt) && isa<ForStmt>(parentStmt);
  });
  checkRule(cursorPair, true);
}
