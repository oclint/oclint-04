#include "mo/exception/MessageBasedException.h"
#include "mo/SmellFinderTest.h"

void SmellFinderTest::setUp() {
  finder = new SmellFinder("test/samples/HelloWorld.m");
}

void SmellFinderTest::tearDown() {
  delete finder;
}

void SmellFinderTest::testHasNoSmell() {
  TS_ASSERT(!finder->hasSmell());
}

void SmellFinderTest::testCodeCompilationFailException() {
  try {
    new SmellFinder("test/samples/CompilationFail.txt");
    TS_FAIL("compilation error exception expected");
  } catch (MessageBasedException *ex) {
    //
  }
}

void SmellFinderTest::testSourceDoesntExistException() {
  try {
    new SmellFinder("");
    TS_FAIL("source file doesn't exist exception expected");
  } catch (MessageBasedException *ex) {
    //
  }
}
