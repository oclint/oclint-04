#include <cxxtest/TestSuite.h>
#include "mo/RuleData.h"

class RuleDataTest : public CxxTest::TestSuite { 
private:
  RuleData *_data;
  
public:
  void setUp();
  void tearDown();
  void testNoRule();
  void testAddRule();
  void testGetRuleOutOfRangeWithNoRule();
  void testGetRuleOutOfRangeWithNegativeIndex();
  void testGetRuleOutOfRangeWithIndexOverNumberOfRules();
  void testNoViolation();
  void testAddViolation();
  void testGetViolations();
};
