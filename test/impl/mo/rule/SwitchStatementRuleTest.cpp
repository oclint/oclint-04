#include "mo/rule/SwitchStatementRuleTest.h"
#include "mo/RuleData.h"
#include "mo/RuleViolation.h"

#include <clang/AST/Stmt.h>

using namespace clang;

CXCursor stmtCursor() {
  CXCursor cursor;
  cursor.kind = CXCursor_UnexposedStmt;
  Stmt stmt(Stmt::SwitchStmtClass);
  cursor.data[1] = &stmt;
  return cursor;
}

void SwitchStatementRuleTest::setUp() {
  rule = new SwitchStatementRule();
}

void SwitchStatementRuleTest::tearDown() {
  delete rule;
}

#include "mo/SmellFinder.h"

void SwitchStatementRuleTest::testApply() {
  /*
  RuleData data;
  rule->apply(stmtCursor(), clang_getNullCursor(), data);
  TS_ASSERT_EQUALS(data.numberOfViolations(), 1);
  */
  const char * const argv[] = { "test/samples/SwitchStatement.m" };
  TS_ASSERT(SmellFinder().hasSmell(argv, 1));
}

void SwitchStatementRuleTest::testName() {
  TS_ASSERT_EQUALS(rule->name(), "Switch Statement");
}


