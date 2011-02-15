#include <cxxtest/TestSuite.h>
#include "mo/RuleViolation.h"

class RuleViolationTest : public CxxTest::TestSuite { 
private:
  RuleViolation *violation;
  
public:
  void setUp();
  void tearDown();
  void testNoViolation();
  void testAddViolation();
};
