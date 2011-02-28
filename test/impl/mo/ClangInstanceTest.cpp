#include "mo/exception/MOException.h"
#include "mo/ClangInstanceTest.h"
#include "mo/reporter/MockReporter.h"

void ClangInstanceTest::setUp() {
  instance = new ClangInstance();
}

void ClangInstanceTest::tearDown() {
  delete instance;
}


void ClangInstanceTest::testHasNoDiagnostic() {
  const char * const argv[] = { "test/samples/HelloWorld.m" };
  instance->compileSourceFileToTranslationUnit(argv, 1);
  TS_ASSERT(!instance->hasDiagnostic());
}

void ClangInstanceTest::testHasDiagnostic() {
  const char * const argv[] = { "test/samples/CompilerDiagnostics.cpp" };
  instance->compileSourceFileToTranslationUnit(argv, 1);
  TS_ASSERT(instance->hasDiagnostic());
}

void ClangInstanceTest::testCodeCompilationFailException() {
  try {
    const char * const argv[] = { "test/samples/CompilationFail.txt" };
    instance->compileSourceFileToTranslationUnit(argv, 1);
    TS_FAIL("compilation error exception expected");
  } catch (MOException& ex) {
    //
  }
}

void ClangInstanceTest::testReportDiagnostics() {
  const char * const argv[] = { "test/samples/CompilerDiagnostics.cpp" };
  instance->compileSourceFileToTranslationUnit(argv, 1);
  MockReporter reporter;
  TS_ASSERT_EQUALS(instance->reportDiagnostics(reporter), "mock report diagnostics");
}

void ClangInstanceTest::testGetTranslationUnitWithCompilationError() {
  try {
    instance->getTranslationUnit();
    TS_FAIL("empty translation unit exception expected");
  } catch (MOException& ex) {
    //
  }
}

void ClangInstanceTest::testGetTranslationUnitWithDiagnostics() {
  try {
    const char * const argv[] = { "test/samples/CompilerDiagnostics.cpp" };
    instance->compileSourceFileToTranslationUnit(argv, 1);
    instance->getTranslationUnit();
    TS_FAIL("questionable translation unit exception expected");
  } catch (MOException& ex) {
    //
  }
}

void ClangInstanceTest::testGetTranslationUnit() {
  const char * const argv[] = { "test/samples/HelloWorld.m" };
  instance->compileSourceFileToTranslationUnit(argv, 1);
  CXTranslationUnit translationUnit = instance->getTranslationUnit();
  TS_ASSERT(translationUnit);
  TS_ASSERT(!clang_getNumDiagnostics(translationUnit));
}
