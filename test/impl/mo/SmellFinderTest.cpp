#include "mo/exception/MOException.h"
#include "mo/SmellFinderTest.h"
#include "mo/reporter/MockReporter.h"
#include "mo/util/StringSourceCodeToTranslationUnitUtil.h"

void SmellFinderTest::setUp() {
  _finder = new SmellFinder();
  _index = clang_createIndex(0, 0);
  _translationUnit = NULL;
}

void SmellFinderTest::tearDown() {
  delete _finder;
  clang_disposeTranslationUnit(_translationUnit); 
  clang_disposeIndex(_index);
}

void SmellFinderTest::testNoSmellWithoutRunningFinder() {
  TS_ASSERT_EQUALS(_finder->numberOfViolations(), 0);
}

void SmellFinderTest::testHasNoSmell() {
  string stringToBeChecked = "int main() { return 0; }";
  StringSourceCode strCode(stringToBeChecked, "m");
  _translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(strCode, _index);
  TS_ASSERT(!_finder->hasSmell(_translationUnit));
  TS_ASSERT_EQUALS(_finder->numberOfViolations(), 0);
}

void SmellFinderTest::testHasSmellWithEmptyTranslationUnit() {
  try {
    _finder->hasSmell(0);
    TS_FAIL("inpection on empty tranlsation unit exception expected");
  } catch (MOException& ex) {
    // :)
  }
}

void SmellFinderTest::testReportViolations() {
  string stringToBeChecked = "int main() { int i = 1; switch (i) { } return 0; }";
  StringSourceCode strCode(stringToBeChecked, "m");
  _translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(strCode, _index);
  TS_ASSERT(_finder->hasSmell(_translationUnit));
  TS_ASSERT_EQUALS(_finder->numberOfViolations(), 1);
  MockReporter reporter;
  TS_ASSERT_EQUALS(_finder->reportSmells(reporter), "mock report violations");
}
