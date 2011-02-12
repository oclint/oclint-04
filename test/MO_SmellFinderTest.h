#include <cxxtest/TestSuite.h>
#include "mo/SmellFinder.h"

class SmellFinderTest : public CxxTest::TestSuite { 
private:
  SmellFinder *finder;
public:
  void setUp() {
    finder = new SmellFinder();
  }
  
  void tearDown() {
    delete finder;
  }
  
  void testHasNoSmell() {
    TS_ASSERT(!finder->hasSmell(""));
  }
};
