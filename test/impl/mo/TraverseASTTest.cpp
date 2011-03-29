#include "mo/TraverseASTTest.h"
#include "mo/rule/MockRule.h"
#include "mo/RuleData.h"
#include "mo/RuleViolation.h"

void TraverseASTTest::testTraverseAST() {
  RuleData *data = new RuleData();
  CXCursor node = clang_getNullCursor();
  CXCursor parentNode = clang_getNullCursor();
  TS_ASSERT_EQUALS(traverseAST(node, parentNode, data), CXChildVisit_Recurse);
  TS_ASSERT_EQUALS(data->numberOfViolations(), 1);
}
