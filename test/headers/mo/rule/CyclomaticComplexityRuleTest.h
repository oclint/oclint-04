#include <cxxtest/TestSuite.h>
#include "mo/rule/CyclomaticComplexityRule.h"

class CyclomaticComplexityRuleTest : public CxxTest::TestSuite { 
private:
  CyclomaticComplexityRule *_rule;
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testCCNNineIsNotASmell();
  void testCCNTenIsASmell();
  void testCCNElevenIsASmell();
};
