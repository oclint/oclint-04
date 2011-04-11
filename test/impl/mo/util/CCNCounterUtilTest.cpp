#include "mo/util/CCNCounterUtilTest.h"

void CCNCounterUtilTest::testOneIfStatement() {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, "test/samples/EmptyIfStatement.m", 0, 0, 0, 0, CXTranslationUnit_None);
  TS_ASSERT_EQUALS(CCNCounterUtil::getCCNOfCursor(clang_getTranslationUnitCursor(translationUnit)), 1);
}
