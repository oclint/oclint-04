#include "mo/util/CCNCounterUtilTest.h"
#include "mo/util/StringSourceCodeToTranslationUnitUtil.h"

void CCNCounterUtilTest::setUp() {
  _index = clang_createIndex(0, 0);
  _translationUnit = NULL;
}

void CCNCounterUtilTest::tearDown() {
  clang_disposeTranslationUnit(_translationUnit); 
  clang_disposeIndex(_index);
}

void CCNCounterUtilTest::checkCCN(StringSourceCode sourceCode, int expectedCCN) {
  _translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(sourceCode, _index);
  TS_ASSERT_EQUALS(CCNCounterUtil::getCCNOfCursor(clang_getTranslationUnitCursor(_translationUnit)), expectedCCN);
}

void CCNCounterUtilTest::testNoDecisionPoint() {
  StringSourceCode strCode("int main() { return 0; }", "m");
  checkCCN(strCode, 1);
}

void CCNCounterUtilTest::testOneIfStatement() {
  StringSourceCode strCode("int main() { if (1) {} return 0; }", "m");
  checkCCN(strCode, 2);
}

void CCNCounterUtilTest::testOneForStatement() {
  StringSourceCode strCode("int main() { for(;;) {} return 0; }", "m");
  checkCCN(strCode, 2);
}

void CCNCounterUtilTest::testOneObjCForCollectionStatement() {
  StringSourceCode strCode("int main() { id array; for(id one in array) {} return 0; }", "m");
  checkCCN(strCode, 2);
}

void CCNCounterUtilTest::testOneWhileStatement() {
  StringSourceCode strCode("int main() { while(1) {} return 0; }", "m");
  checkCCN(strCode, 2);
}

void CCNCounterUtilTest::testOneDoStatement() {
  StringSourceCode strCode("int main() { do {} while(1); return 0; }", "m");
  checkCCN(strCode, 2);
}

void CCNCounterUtilTest::testOneCaseStatement() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  checkCCN(strCode, 2);
}

void CCNCounterUtilTest::testTwoCaseStatements() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: case 2: break; } return 0; }", "m");
  checkCCN(strCode, 3);
}

void CCNCounterUtilTest::testOneObjCAtCatchStatement() {
  StringSourceCode strCode("int main() { @try {} @catch (id ex) {} return 0; }", "m");
  checkCCN(strCode, 2);
}

void CCNCounterUtilTest::testOneConditionalOperator() {
  StringSourceCode strCode("int main() { int i = 0 ? 1 : -1; return i; }", "m");
  checkCCN(strCode, 2);
}

void CCNCounterUtilTest::testOneLogicAndOperator() {
  StringSourceCode strCode("int main() { bool b = 1 && 0; return 0; }", "m");
  //checkCCN(strCode, 2);
}

void CCNCounterUtilTest::testOneLogicOrOperator() {
  StringSourceCode strCode("int main() { bool b = 1 || 0; return 0; }", "m");
  //checkCCN(strCode, 2);
}
