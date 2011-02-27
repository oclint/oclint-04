#include "mo/exception/MOException.h"
#include "mo/SmellFinderTest.h"
#include "mo/reporter/MockReporter.h"

void SmellFinderTest::setUp() {
  finder = new SmellFinder();
}

void SmellFinderTest::tearDown() {
  delete finder;
}


void SmellFinderTest::testHasNoDiagnostic() {
  const char * const argv[] = { "test/samples/HelloWorld.m" };
  finder->compileSourceFileToTranslationUnit(argv, 1);
  TS_ASSERT(!finder->hasDiagnostic());
}

void SmellFinderTest::testHasDiagnostic() {
  const char * const argv[] = { "test/samples/CompilerDiagnostics.cpp" };
  finder->compileSourceFileToTranslationUnit(argv, 1);
  TS_ASSERT(finder->hasDiagnostic());
}

void SmellFinderTest::testHasNoSmell() {
  const char * const argv[] = { "test/samples/HelloWorld.m" };
  finder->compileSourceFileToTranslationUnit(argv, 1);
  TS_ASSERT(!finder->hasSmell());
}

void SmellFinderTest::testCodeCompilationFailException() {
  try {
    const char * const argv[] = { "test/samples/CompilationFail.txt" };
    finder->compileSourceFileToTranslationUnit(argv, 1);
    TS_FAIL("compilation error exception expected");
  } catch (MOException& ex) {
    //
  }
}

void SmellFinderTest::testReportDiagnostics() {
  const char * const argv[] = { "test/samples/CompilerDiagnostics.cpp" };
  finder->compileSourceFileToTranslationUnit(argv, 1);
  MockReporter reporter;
  TS_ASSERT_EQUALS(finder->reportDiagnostics(reporter), "mock report diagnostics");
}

void SmellFinderTest::testReportViolations() {
  const char * const argv[] = { "test/samples/HelloWorld.m" };
  finder->compileSourceFileToTranslationUnit(argv, 1);
  MockReporter reporter;
  TS_ASSERT_EQUALS(finder->reportSmells(reporter), "mock report violations");
}
