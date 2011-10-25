#include "oclint/util/CyclomaticComplexityMeasurementTest.h"
#include "oclint/util/StringSourceCodeToTranslationUnitUtil.h"

void CyclomaticComplexityMeasurementTest::setUp() {
  _index = clang_createIndex(0, 0);
  _translationUnit = NULL;
}

void CyclomaticComplexityMeasurementTest::tearDown() {
  clang_disposeTranslationUnit(_translationUnit); 
  clang_disposeIndex(_index);
}

void CyclomaticComplexityMeasurementTest::checkCCN(StringSourceCode sourceCode, int expectedCCN) {
  _translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(sourceCode, _index);
  TS_ASSERT_EQUALS(CyclomaticComplexityMeasurement::getCCNOfCursor(clang_getTranslationUnitCursor(_translationUnit)), expectedCCN);
}

void CyclomaticComplexityMeasurementTest::testNoDecisionPoint() {
  StringSourceCode strCode("int main() { return 0; }", "m");
  checkCCN(strCode, 1);
}

void CyclomaticComplexityMeasurementTest::testOneIfStatement() {
  StringSourceCode strCode("int main() { if (1) {} return 0; }", "m");
  checkCCN(strCode, 2);
}

void CyclomaticComplexityMeasurementTest::testOneForStatement() {
  StringSourceCode strCode("int main() { for(;;) {} return 0; }", "m");
  checkCCN(strCode, 2);
}

void CyclomaticComplexityMeasurementTest::testOneObjCForCollectionStatement() {
  StringSourceCode strCode("int main() { id array; for(id one in array) {} return 0; }", "m");
  checkCCN(strCode, 2);
}

void CyclomaticComplexityMeasurementTest::testOneWhileStatement() {
  StringSourceCode strCode("int main() { while(1) {} return 0; }", "m");
  checkCCN(strCode, 2);
}

void CyclomaticComplexityMeasurementTest::testOneDoStatement() {
  StringSourceCode strCode("int main() { do {} while(1); return 0; }", "m");
  checkCCN(strCode, 2);
}

void CyclomaticComplexityMeasurementTest::testOneCaseStatement() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  checkCCN(strCode, 2);
}

void CyclomaticComplexityMeasurementTest::testTwoCaseStatements() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: case 2: break; } return 0; }", "m");
  checkCCN(strCode, 3);
}

void CyclomaticComplexityMeasurementTest::testOneObjCAtCatchStatement() {
  StringSourceCode strCode("int main() { @try {} @catch (id ex) {} return 0; }", "m");
  checkCCN(strCode, 2);
}

void CyclomaticComplexityMeasurementTest::testOneConditionalOperator() {
  StringSourceCode strCode("int main() { int i = 0 ? 1 : -1; return i; }", "m");
  checkCCN(strCode, 2);
}

void CyclomaticComplexityMeasurementTest::testOneLogicAndOperator() {
  StringSourceCode strCode("int main() { int b = 1 && 0; return 0; }", "m");
  checkCCN(strCode, 2);
}

void CyclomaticComplexityMeasurementTest::testOneLogicOrOperator() {
  StringSourceCode strCode("int main() { int b = 1 || 0; return 0; }", "m");
  checkCCN(strCode, 2);
}

void CyclomaticComplexityMeasurementTest::testABinaryOperatorButHasNoEffectOnCCNCouting() {
  StringSourceCode strCode("int main() { int b = 1 == 0; return 0; }", "m");
  checkCCN(strCode, 1);
}
