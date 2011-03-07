#include "mo/exception/MOException.h"
#include "mo/ClangInstanceTest.h"
#include "mo/reporter/MockReporter.h"

void ClangInstanceTest::setUp() {
  _instance = new ClangInstance();
}

void ClangInstanceTest::tearDown() {
  delete _instance;
}


void ClangInstanceTest::testHasNoDiagnostic() {
  const char * const argv[] = { "test/samples/HelloWorld.m" };
  _instance->compileSourceFileToTranslationUnit(argv, 1);
  TS_ASSERT(!_instance->hasDiagnostic());
}

void ClangInstanceTest::testHasDiagnostic() {
  const char * const argv[] = { "test/samples/CompilerDiagnostics.cpp" };
  _instance->compileSourceFileToTranslationUnit(argv, 1);
  TS_ASSERT(_instance->hasDiagnostic());
}

void ClangInstanceTest::testCodeCompilationFailException() {
  try {
    const char * const argv[] = { "test/samples/CompilationFail.txt" };
    _instance->compileSourceFileToTranslationUnit(argv, 1);
    TS_FAIL("compilation error exception expected");
  } catch (MOException& ex) {
    //
  }
}

void ClangInstanceTest::testReportDiagnostics() {
  const char * const argv[] = { "test/samples/CompilerDiagnostics.cpp" };
  _instance->compileSourceFileToTranslationUnit(argv, 1);
  MockReporter reporter;
  TS_ASSERT_EQUALS(_instance->reportDiagnostics(reporter), "mock report diagnostics");
}

void ClangInstanceTest::testGetTranslationUnitWithCompilationError() {
  try {
    _instance->getTranslationUnit();
    TS_FAIL("empty translation unit exception expected");
  } catch (MOException& ex) {
    //
  }
}

void ClangInstanceTest::testGetTranslationUnitWithDiagnostics() {
  try {
    const char * const argv[] = { "test/samples/CompilerDiagnostics.cpp" };
    _instance->compileSourceFileToTranslationUnit(argv, 1);
    _instance->getTranslationUnit();
    TS_FAIL("questionable translation unit exception expected");
  } catch (MOException& ex) {
    //
  }
}

void ClangInstanceTest::testGetTranslationUnit() {
  const char * const argv[] = { "test/samples/HelloWorld.m" };
  _instance->compileSourceFileToTranslationUnit(argv, 1);
  CXTranslationUnit translationUnit = _instance->getTranslationUnit();
  TS_ASSERT(translationUnit);
  TS_ASSERT(!clang_getNumDiagnostics(translationUnit));
}
