#include <cxxtest/TestSuite.h>
#include "oclint/ViolationSet.h"

class ViolationSetTest : public CxxTest::TestSuite { 
private:
  ViolationSet *_violationSet;
  
public:
  void setUp();
  void tearDown();
  void testNoViolation();
  void testAddViolation();
  void testGetViolations();
};
