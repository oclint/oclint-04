#include <cxxtest/TestSuite.h>
#include "test/mock/MockRule.h"
#include "test/mock/MockViolation.h"

using namespace clang;

class ViolationTest : public CxxTest::TestSuite { 
private:
  MockViolation *violation;
public:
  void setUp() {
    violation = new MockViolation();
  }
  
  void tearDown() {
    delete violation;
  }
  
  void testInitViolation() {
    TS_ASSERT_EQUALS(violation->numberOfViolations(), 0);
  }
  
  void testAddViolationWithRuleViolationObjectWithoutMessage() {
    RuleViolation *aViolation = new RuleViolation(createViolatedSourceRange(), createViolatedRule());
    violation->addViolation(aViolation);
    TS_ASSERT_EQUALS(violation->numberOfViolations(), 1);
    RuleViolation *addedViolation = violation->violation(0);
    TS_ASSERT_EQUALS(addedViolation->getMessage(), "");
  }
  
  void testAddViolationWithRuleViolationObjectWithMessage() {
    RuleViolation *aViolation = new RuleViolation(createViolatedSourceRange(), createViolatedRule(), createViolatedMessage());
    violation->addViolation(aViolation);
    TS_ASSERT_EQUALS(violation->numberOfViolations(), 1);
    RuleViolation *addedViolation = violation->violation(0);
    TS_ASSERT_EQUALS(addedViolation->getMessage(), "violate mock rule");
  }
  
  void testAddViolationWithViolatedAttributesWithoutMessage() {
    violation->addViolation(createViolatedSourceRange(), createViolatedRule());
    TS_ASSERT_EQUALS(violation->numberOfViolations(), 1);
    RuleViolation *addedViolation = violation->violation(0);
    TS_ASSERT_EQUALS(addedViolation->getMessage(), "");
  }
  
  void testAddViolationWithViolatedAttributesWithMessage() {
    violation->addViolation(createViolatedSourceRange(), createViolatedRule(), createViolatedMessage());
    TS_ASSERT_EQUALS(violation->numberOfViolations(), 1);
    RuleViolation *addedViolation = violation->violation(0);
    TS_ASSERT_EQUALS(addedViolation->getMessage(), "violate mock rule");
  }
  
  void testIndexWithinViolationRangeWithNoViolation() {
    TS_ASSERT(!violation->indexWithinRange(-1));
    TS_ASSERT(!violation->indexWithinRange(0));
    TS_ASSERT(!violation->indexWithinRange(1));
  }
  
  void testIndexWithinViolationRangeWithOneViolation() {
    violation->addViolation(createViolatedSourceRange(), createViolatedRule());
    TS_ASSERT(!violation->indexWithinRange(-1));
    TS_ASSERT(violation->indexWithinRange(0));
    TS_ASSERT(!violation->indexWithinRange(1));
  }
  
  void testIndexWithinViolationRangeWithTwoViolations() {
    violation->addViolation(createViolatedSourceRange(), createViolatedRule());
    violation->addViolation(createViolatedSourceRange(), createViolatedRule());
    TS_ASSERT(!violation->indexWithinRange(-1));
    TS_ASSERT(violation->indexWithinRange(0));
    TS_ASSERT(violation->indexWithinRange(1));
    TS_ASSERT(!violation->indexWithinRange(2));
  }
  
  void testIndexOutOfRangeExceptionWithNoViolation() {
    TS_ASSERT_THROWS_EQUALS(violation->violation(0), MessageBasedException &ex, 
      ex.getExceptionMessage(), "Index out of range when trying to get a certain RuleViolation!");
  }
  
private:
  AbstractRule *createViolatedRule() {
    return new MockRule();
  }
  
  SourceRange createViolatedSourceRange() {
    return SourceRange(SourceLocation(), SourceLocation());
  }
  
  string createViolatedMessage() {
    return "violate mock rule";
  }
};
