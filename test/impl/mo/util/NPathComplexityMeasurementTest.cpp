#include "mo/util/NPathComplexityMeasurementTest.h"
#include "mo/util/CursorExtractionUtil.h"
#include "mo/util/CursorUtil.h"

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
