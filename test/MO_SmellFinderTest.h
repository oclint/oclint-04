#include <cxxtest/TestSuite.h>
#include "mo/SmellFinder.h"

class SmellFinderTest : public CxxTest::TestSuite { 
private:
  SmellFinder *finder;
public:
  void setUp() {
    finder = new SmellFinder("test/resource/HelloWorld.m");
  }
  
  void tearDown() {
    delete finder;
  }
  
  void testHasNoSmell() {
    TS_ASSERT(!finder->hasSmell());
  }
  
  void testCodeCompilationFailException() {
    TS_ASSERT_THROWS_ANYTHING(new SmellFinder(""));
  }
};
