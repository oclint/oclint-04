#include <cxxtest/TestSuite.h>
#include "mo/RuleData.h"

class RuleDataTest : public CxxTest::TestSuite { 
private:
  RuleData *data;
  
public:
  void setUp();
  void tearDown();
  void testNoViolation();
  void testAddViolation();
  void testGetViolationOutOfRangeWithNoViolation();
  void testGetViolationOutOfRangeWithNegativeIndex();
  void testGetViolationOutOfRangeWithIndexOverNumberOfViolations();
};
