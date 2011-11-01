#include "oclint/rule/UnreachableCodeRuleTest.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/StringSourceCode.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/CursorExtractionHelper.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/StmtObjC.h>

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
    Stmt *stmt = CursorHelper::getStmt(node);
    return stmt && isa<CompoundStmt>(stmt);
  });
  checkRule(cursorPair, isViolated);
}

template<typename nodeType, typename parentNodeType> 
void UnreachableCodeRuleTest::checkRuleOn(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorHelper::getStmt(node);
    Stmt *parentStmt = CursorHelper::getStmt(parentNode);
    return stmt && parentStmt && isa<nodeType>(stmt) && isa<parentNodeType>(parentStmt);
  });
  checkRule(cursorPair, isViolated);
}

void UnreachableCodeRuleTest::testGoodCompoundStmtWithoutReturnStmt() {
  checkRuleOnFunctionRootComponent("void aMethod() { int a; a = 1; a = 2; }", false);
}

void UnreachableCodeRuleTest::testGoodCompoundStmtWithReturnStmtAtLastLine() {
  checkRuleOnFunctionRootComponent("int aMethod() { int i = 1; return i; }", false);
}

void UnreachableCodeRuleTest::testCodeAfterReturnStatement() {
  checkRuleOnFunctionRootComponent("int aMethod() { return 1; int i = 1; i++; }", true);
}

void UnreachableCodeRuleTest::testCodeAfterBreakStatementInForStatement() {
  checkRuleOn<CompoundStmt, ForStmt>("int aMethod() { for(;;) { break; int i = 1; i++; } }", true);
}

void UnreachableCodeRuleTest::testCodeAfterContinueStatementInForStatement() {
  checkRuleOn<CompoundStmt, ForStmt>("int aMethod() { for(;;) { continue; int i = 1; i++; } }", true);
}

void UnreachableCodeRuleTest::testCodeAfterReturnStatementInForStatement() {
  checkRuleOn<CompoundStmt, ForStmt>("int aMethod() { for(;;) { return 1; int i = 1; i++; } }", true);
}

void UnreachableCodeRuleTest::testCodeAfterBreakStatementInObjCForCollectionStatement() {
  string strSource = "@implementation ClassName\n- (void)aMethod { \
    id anArray; for (id item in anArray) { break; int i = 1; i++; } }\n@end";
  checkRuleOn<CompoundStmt, ObjCForCollectionStmt>(strSource, true);
}

void UnreachableCodeRuleTest::testCodeAfterContinueStatementInObjCForCollectionStatement() {
  string strSource = "@implementation ClassName\n- (void)aMethod { \
    id anArray; for (id item in anArray) { continue; int i = 1; i++; } }\n@end";
  checkRuleOn<CompoundStmt, ObjCForCollectionStmt>(strSource, true);
}

void UnreachableCodeRuleTest::testCodeAfterReturnStatementInObjCForCollectionStatement() {
  string strSource = "@implementation ClassName\n- (void)aMethod { \
    id anArray; for (id item in anArray) { return; int i = 1; i++; } }\n@end";
  checkRuleOn<CompoundStmt, ObjCForCollectionStmt>(strSource, true);
}

void UnreachableCodeRuleTest::testCodeAfterBreakStatementInWhileStatement() {
  checkRuleOn<CompoundStmt, WhileStmt>("int aMethod() { while(1) { break; int i = 1; i++; } }", true);
}

void UnreachableCodeRuleTest::testCodeAfterContinueStatementInWhileStatement() {
  checkRuleOn<CompoundStmt, WhileStmt>("int aMethod() { while(1) { continue; int i = 1; i++; } }", true);
}

void UnreachableCodeRuleTest::testCodeAfterReturnStatementInWhileStatement() {
  checkRuleOn<CompoundStmt, WhileStmt>("int aMethod() { while(1) { return 1; int i = 1; i++; } }", true);
}

void UnreachableCodeRuleTest::testCodeAfterBreakStatementInDoWhileStatement() {
  checkRuleOn<CompoundStmt, DoStmt>("int aMethod() { do { break; int i = 1; i++; } while(1); }", true);
}

void UnreachableCodeRuleTest::testCodeAfterContinueStatementInDoWhileStatement() {
  checkRuleOn<CompoundStmt, DoStmt>("int aMethod() { do { continue; int i = 1; i++; } while(1); }", true);
}

void UnreachableCodeRuleTest::testCodeAfterReturnStatementInDoWhileStatement() {
  checkRuleOn<CompoundStmt, DoStmt>("int aMethod() { do { return 1; int i = 1; i++; } while(1); }", true);
}
