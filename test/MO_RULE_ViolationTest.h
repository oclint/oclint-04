#include <cxxtest/TestSuite.h>
#include "test/mock/MockRule.h"
#include "test/mock/MockViolation.h"
#include "test/mock/MockStmt.h"
#include "test/mock/MockDecl.h"

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
  
  void testViolatingStmtByApplyingRule() {
    MockStmt stmt;
    MockRule *applyingRule = new MockRule();
    applyingRule->applyStmt(&stmt, *violation);
    TS_ASSERT_EQUALS(violation->numberOfViolations(), 1);
    RuleViolation *addedViolation = violation->violation(0);
    TS_ASSERT_EQUALS(addedViolation->getMessage(), "violate statement when applying mock rule");
    AbstractRule *violatedRule = addedViolation->getRule();
    TS_ASSERT_EQUALS(violatedRule->name(), "MockRule");
    TS_ASSERT_EQUALS(violatedRule->priority(), 99);
  }
  
  void testViolatingDeclByApplyingRule() {
    MockRule *applyingRule = new MockRule();
    applyingRule->applyDecl(new MockDecl(), *violation);
    TS_ASSERT_EQUALS(violation->numberOfViolations(), 1);
    RuleViolation *addedViolation = violation->violation(0);
    TS_ASSERT_EQUALS(addedViolation->getMessage(), "violate declaration when applying mock rule");
    AbstractRule *violatedRule = addedViolation->getRule();
    TS_ASSERT_EQUALS(violatedRule->name(), "MockRule");
    TS_ASSERT_EQUALS(violatedRule->priority(), 99);
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
