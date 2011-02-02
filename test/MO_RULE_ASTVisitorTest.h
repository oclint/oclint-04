#include <cxxtest/TestSuite.h>
#include "mo/rule/ASTVisitor.h"
#include "test/mock/MockStmt.h"
#include "test/mock/MockDecl.h"
#include "test/mock/MockRule.h"

using namespace clang;

class ASTVisitorTest : public CxxTest::TestSuite { 
private:
  ASTVisitor *visitor;
  Violation *violation;
  vector<AbstractRule*> rules;
  
public:
  void setUp() {
    MockRule *rule = new MockRule();
    rules.push_back(rule);
    violation = new Violation();
    visitor = new ASTVisitor(rules, violation);
  }
  
  void tearDown() {
    rules.clear();
    delete violation;
    delete visitor;
  }
  
  void testTraverseStmt() {
    MockStmt stmt;
    TS_ASSERT(visitor->traverse(&stmt));
  }
  
  void testTraverseDecl() {
    TS_ASSERT(visitor->traverse(new MockDecl()));
  }
  
  void testTraverseAndApplyMockRuleToMockStmt() {
    TS_ASSERT_EQUALS(violation->numberOfViolations(), 0);
    MockStmt stmt;
    visitor->traverse(&stmt);
    TS_ASSERT_EQUALS(violation->numberOfViolations(), 1);
    RuleViolation *addedViolation = violation->violation(0);
    TS_ASSERT_EQUALS(addedViolation->getMessage(), "violate statement when applying mock rule");
    AbstractRule *violatedRule = addedViolation->getRule();
    TS_ASSERT_EQUALS(violatedRule->name(), "MockRule");
    TS_ASSERT_EQUALS(violatedRule->priority(), 99);
  }
  
  void testTraverseAndApplyMockRuleToMockDecl() {
    TS_ASSERT_EQUALS(violation->numberOfViolations(), 0);
    visitor->traverse(new MockDecl());
    TS_ASSERT_EQUALS(violation->numberOfViolations(), 1);
    RuleViolation *addedViolation = violation->violation(0);
    TS_ASSERT_EQUALS(addedViolation->getMessage(), "violate declaration when applying mock rule");
    AbstractRule *violatedRule = addedViolation->getRule();
    TS_ASSERT_EQUALS(violatedRule->name(), "MockRule");
    TS_ASSERT_EQUALS(violatedRule->priority(), 99);
  }
};
