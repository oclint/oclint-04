#include "mo/TraverseASTTest.h"
#include "mo/rule/MockRule.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"

void TraverseASTTest::testTraverseAST() {
  ViolationSet *violationSet = new ViolationSet();
  CXCursor node = clang_getNullCursor();
  CXCursor parentNode = clang_getNullCursor();
  TS_ASSERT_EQUALS(traverseAST(node, parentNode, violationSet), CXChildVisit_Recurse);
  TS_ASSERT_EQUALS(violationSet->numberOfViolations(), 1);
}
