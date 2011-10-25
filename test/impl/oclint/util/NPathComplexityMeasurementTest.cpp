#include "oclint/util/NPathComplexityMeasurementTest.h"
#include "oclint/util/CursorExtractionUtil.h"
#include "oclint/util/CursorUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

void NPathComplexityMeasurementTest::checkNPath(string sourceCode, int expectedNPath) {
  StringSourceCode strCode(sourceCode, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorUtil::getStmt(node);
    return stmt && isa<CompoundStmt>(stmt);
  });
  TS_ASSERT_EQUALS(NPathComplexityMeasurement::getNPathOfCursor(cursorPair.first), expectedNPath);
}

void NPathComplexityMeasurementTest::testEmptyMethod() {
  checkNPath("void main() { }", 1);
}

void NPathComplexityMeasurementTest::testIfStatementWithConstantConditionAndEmptyThenCompoundStmt() {
  checkNPath("void main() { if (1) {} }", 2);
}

void NPathComplexityMeasurementTest::testIfStatementWithOneLogicAndOperatorConditionAndEmptyThenCompoundStmt() {
  checkNPath("void main() { if (1 && 0) {} }", 3);
}

void NPathComplexityMeasurementTest::testIfStatementWithOneLogicOrOperatorConditionAndEmptyThenCompoundStmt() {
  checkNPath("void main() { if (1 || 0) {} }", 3);
}

void NPathComplexityMeasurementTest::testIfStatementWithMultipleLogicAndOrOperatorsConditionAndEmptyThenCompoundStmt() {
  checkNPath("void main() { if (0 || 1 && 2) {} }", 4);
}

void NPathComplexityMeasurementTest::testIfElseStatementWithConstantConditionAndEmptyThenCompoundStmt() {
  checkNPath("void main() { if (1) {} else {} }", 2);
}

void NPathComplexityMeasurementTest::testIfElseStatementWithOneLogicAndOperatorConditionAndEmptyThenCompoundStmt() {
  checkNPath("void main() { if (1 && 0) {} else {} }", 3);
}

void NPathComplexityMeasurementTest::testIfElseStatementWithOneLogicOrOperatorConditionAndEmptyThenCompoundStmt() {
  checkNPath("void main() { if (1 || 0) {} else {} }", 3);
}

void NPathComplexityMeasurementTest::testIfElseStatementWithMultipleLogicAndOrOperatorsConditionAndEmptyThenCompoundStmt() {
  checkNPath("void main() { if (0 || 1 && 2) {} else {} }", 4);
}

void NPathComplexityMeasurementTest::testNestedIfStatement() {
  checkNPath("void main() { if (1) { if (1) {} } }", 3);
}

void NPathComplexityMeasurementTest::testNestedIfElseStatement() {
  checkNPath("void main() { if (1) { if (1) {} else {} } else { if (1) {} else {} } }", 4);
}

void NPathComplexityMeasurementTest::testWhileStatementWithConstantConditionAndEmptyCompoundStmt() {
  checkNPath("void main() { while (1) {} }", 2);
}

void NPathComplexityMeasurementTest::testWhileStatementWithOneLogicAndOperatorConditionAndEmptyCompoundStmt() {
  checkNPath("void main() { while (1 && 0) {} }", 3);
}

void NPathComplexityMeasurementTest::testWhileStatementWithOneLogicOrOperatorConditionAndEmptyCompoundStmt() {
  checkNPath("void main() { while (1 || 0) {} }", 3);
}

void NPathComplexityMeasurementTest::testDoWhileStatementWithConstantConditionAndEmptyCompoundStmt() {
  checkNPath("void main() { do {} while (1); }", 2);
}

void NPathComplexityMeasurementTest::testDoWhileStatementWithOneLogicAndOperatorConditionAndEmptyCompoundStmt() {
  checkNPath("void main() { do {} while (1 && 0); }", 3);
}

void NPathComplexityMeasurementTest::testDoWhileStatementWithOneLogicOrOperatorConditionAndEmptyCompoundStmt() {
  checkNPath("void main() { do {} while (1 || 0); }", 3);
}

void NPathComplexityMeasurementTest::testForStatementWithSimpleConditionAndEmptyCompoundStmt() {
  checkNPath("void main() { for (int i = 0; i < 1; i++) {} }", 3);
}

void NPathComplexityMeasurementTest::testForStatementWithOneLogicAndOperatorConditionAndEmptyCompoundStmt() {
  checkNPath("void main() { for (int i = 0; i < 1 && 0; i++) {} }", 4);
}

void NPathComplexityMeasurementTest::testForeachStatementWithEmptyCompoundStmt() {
  checkNPath("void main() { id anArray; for (id it in anArray) {} }", 3);
}

void NPathComplexityMeasurementTest::testForeachStatementWithCompoundStmtWithIfStmt() {
  checkNPath("void main() { id anArray; for (id it in anArray) { if (1) {} } }", 4);
}

void NPathComplexityMeasurementTest::testSwitchStatementWithSimpleConditionAndEmptyBody() {
  checkNPath("void main() { int i; switch (i) {} }", 0);
}

void NPathComplexityMeasurementTest::testSwitchStatementWithSimpleConditionAndOneCase() {
  checkNPath("void main() { int i; switch (i) { case 1: break; } }", 1);
}

void NPathComplexityMeasurementTest::testSwitchStatementWithSimpleConditionAndOneCaseOneDefault() {
  checkNPath("void main() { int i; switch (i) { case 1: break; default: break; } }", 2);
}

void NPathComplexityMeasurementTest::testSwitchStatementWithSimpleConditionAndTwoCasesOneDefault() {
  checkNPath("void main() { int i; switch (i) { case 1: break; case 2: break; default: break; } }", 3);
}

void NPathComplexityMeasurementTest::testSwitchStatementWithOneLogicAndOperatorConditionAndTwoCasesOneDefault() {
  checkNPath("void main() { int i, j; switch (i && j) { case 1: break; case 0: break; default: break; } }", 4);
}

void NPathComplexityMeasurementTest::testSwitchStatementWithSimpleConditionAndOneCaseOneIfOneDefault() {
  checkNPath("void main() { int i; switch (i) { case 1: break; if (i > 0 && i < 0) {} default: break; } }", 4);
}

void NPathComplexityMeasurementTest::testSwitchStatementWithSimpleConditionAndOneCaseAsIfOneDefault() {
  checkNPath("void main() { int i; switch (i) { case 1: if (i > 0 && i < 0) {} break; default: break; } }", 4);
}

void NPathComplexityMeasurementTest::testSwitchStatementWithSimpleConditionAndOneCaseAsTwoIfsOneDefault() {
  checkNPath("void main() { int i; switch (i) { case 1: if (i > 0) {} if (i < 0) {} break; default: break; } }", 5);
}

void NPathComplexityMeasurementTest::testBasicConditionalOperator() {
  checkNPath("void main() { if (1 ? 2 : 3) {} }", 4);
}

void NPathComplexityMeasurementTest::testNastingConditionalOperator() {
  checkNPath("void main() { if (1 ? (2 ? 3 : 4) : (5 ? 6 : 7)) {} }", 8);
}
