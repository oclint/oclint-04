#include "mo/exception/MOException.h"
#include "mo/SmellFinderTest.h"

void SmellFinderTest::setUp() {
  finder = new SmellFinder();
}

void SmellFinderTest::tearDown() {
  delete finder;
}

void SmellFinderTest::testHasSmell() {
  TS_ASSERT(finder->hasSmell("test/samples/SwitchStatement.m"));
}

void SmellFinderTest::testHasNoSmell() {
  TS_ASSERT(!finder->hasSmell("test/samples/HelloWorld.m"));
}

void SmellFinderTest::testCodeCompilationFailException() {
  try {
    finder->compileSourceFileToTranslationUnit("test/samples/CompilationFail.txt");
    TS_FAIL("compilation error exception expected");
  } catch (MOException *ex) {
    //
  }
}

void SmellFinderTest::testSourceDoesntExistException() {
  try {
    finder->compileSourceFileToTranslationUnit("");
    TS_FAIL("source file doesn't exist exception expected");
  } catch (MOException *ex) {
    //
  }
}
