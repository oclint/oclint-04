#include "mo/exception/MOException.h"
#include "mo/SmellFinderTest.h"

void SmellFinderTest::setUp() {
  finder = new SmellFinder();
}

void SmellFinderTest::tearDown() {
  delete finder;
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
