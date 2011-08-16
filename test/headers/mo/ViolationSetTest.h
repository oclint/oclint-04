#include <cxxtest/TestSuite.h>
#include "mo/ViolationSet.h"

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
