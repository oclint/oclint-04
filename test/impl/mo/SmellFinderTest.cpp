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

void SmellFinderTest::testHasNoSmell() {
  string stringToBeChecked = "int main() {\n\
  return 0;                               \n\
}                                         \n";

  StringSourceCode strCode(stringToBeChecked, "m");
  _translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(strCode, _index);
  TS_ASSERT(!_finder->hasSmell(_translationUnit));
}

void SmellFinderTest::testHasSmellWithEmptyTranslationUnit() {
  try {
    _finder->hasSmell(0);
    TS_FAIL("inpection on empty tranlsation unit exception expected");
  } catch (MOException& ex) {
    //
  }
}

void SmellFinderTest::testHasSmellWithQuestionableTranslationUnit() {
  try {
    string src = "test/samples/CompilerDiagnostics.cpp";
    _translationUnit = clang_parseTranslationUnit(_index, src.c_str(), 0, 0, 0, 0, CXTranslationUnit_None);
    _finder->hasSmell(_translationUnit);
    TS_FAIL("inpection on questionalbe tranlsation unit exception expected");
  } catch (MOException& ex) {
    //
  }
}

void SmellFinderTest::testReportViolations() {
  string src = "test/samples/SwitchStatement.m";
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, src.c_str(), 0, 0, 0, 0, CXTranslationUnit_None);
  _finder->hasSmell(translationUnit);
  MockReporter reporter;
  TS_ASSERT_EQUALS(_finder->reportSmells(reporter), "mock report violations");
}
