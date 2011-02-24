#include <cxxtest/TestSuite.h>
#include "mo/SmellFinder.h"

class SmellFinderTest : public CxxTest::TestSuite { 
private:
  SmellFinder *finder;
  
public:
  void setUp();
  void tearDown();
  void testHasNoDiagnostic();
  void testHasDiagnostic();
  void testHasNoSmell();
  void testCodeCompilationFailException();
};
