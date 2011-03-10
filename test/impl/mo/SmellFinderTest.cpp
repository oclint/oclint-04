#include "mo/exception/MOException.h"
#include "mo/SmellFinderTest.h"
#include "mo/reporter/MockReporter.h"

void SmellFinderTest::setUp() {
  _finder = new SmellFinder();
}

void SmellFinderTest::tearDown() {
  delete _finder;
  _finder = NULL;
}

void SmellFinderTest::testHasNoSmell() {
  string src = "test/samples/HelloWorld.m";
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, src.c_str(), 0, 0, 0, 0, CXTranslationUnit_None);
  TS_ASSERT(!_finder->hasSmell(translationUnit));
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
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, src.c_str(), 0, 0, 0, 0, CXTranslationUnit_None);
    _finder->hasSmell(translationUnit);
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
