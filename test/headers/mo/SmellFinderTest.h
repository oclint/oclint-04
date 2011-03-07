#include <cxxtest/TestSuite.h>
#include "mo/SmellFinder.h"

class SmellFinderTest : public CxxTest::TestSuite { 
private:
  SmellFinder *_finder;
  
public:
  void setUp();
  void tearDown();
  void testHasNoSmell();
  void testHasSmellWithEmptyTranslationUnit();
  void testHasSmellWithQuestionableTranslationUnit();
  void testReportNoViolation();
  void testReportViolations();
};
