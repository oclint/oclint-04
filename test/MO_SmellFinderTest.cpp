#include "test/MO_SmellFinderTest.h"

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
    new SmellFinder("");
    TS_FAIL("SmellFinder should throws an exception here");
  } catch (...) {
    //
  }
}
