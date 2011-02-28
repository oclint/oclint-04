#include "mo/exception/MOException.h"
#include "mo/SmellFinderTest.h"
#include "mo/reporter/MockReporter.h"

void SmellFinderTest::setUp() {
  finder = new SmellFinder();
}

void SmellFinderTest::tearDown() {
  delete finder;
}

void SmellFinderTest::testHasNoSmell() {
  string src = "test/samples/HelloWorld.m";
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, src.c_str(), 0, 0, 0, 0, CXTranslationUnit_None);
  TS_ASSERT(!finder->hasSmell(translationUnit));
}

void SmellFinderTest::testHasSmellWithEmptyTranslationUnit() {
  try {
    finder->hasSmell(0);
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
    finder->hasSmell(translationUnit);
    TS_FAIL("inpection on questionalbe tranlsation unit exception expected");
  } catch (MOException& ex) {
    //
  }
}

void SmellFinderTest::testReportNoViolation() {
  try {
    MockReporter reporter;
    finder->reportSmells(reporter);
    TS_FAIL("report on no violation exception expected");
  } catch (MOException& ex) {
    //
  }
}

void SmellFinderTest::testReportViolations() {
  string src = "test/samples/SwitchStatement.m";
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, src.c_str(), 0, 0, 0, 0, CXTranslationUnit_None);
  finder->hasSmell(translationUnit);
  MockReporter reporter;
  TS_ASSERT_EQUALS(finder->reportSmells(reporter), "mock report violations");
}
