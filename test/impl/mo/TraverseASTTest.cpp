#include "mo/TraverseASTTest.h"
#include "mo/rule/MockRule.h"
#include "mo/RuleData.h"
#include "mo/RuleViolation.h"

void TraverseASTTest::testTraverseAST() {
  RuleData *data = new RuleData();
  RuleViolation *violation = new RuleViolation();
  data->setViolation(violation);
  MockRule *rule = new MockRule();
  data->setRule(rule);
  CXCursor node;
  CXCursor parentNode;
  TS_ASSERT_EQUALS(rule->name(), "mock rule");
  TS_ASSERT_EQUALS(traverseAST(node, parentNode, data), CXChildVisit_Recurse);
  TS_ASSERT_EQUALS(rule->name(), "applied!");
  TS_ASSERT_EQUALS(violation->numberOfViolations(), 1);
}
