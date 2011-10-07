#include <cxxtest/TestSuite.h>
#include "mo/rule/RedundantLocalVariableRule.h"

class RedundantLocalVariableRuleTest : public CxxTest::TestSuite { 
private:
  RedundantLocalVariableRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testNoRedundantLocalVariable();
  void testRedundantDeclarationVariableFollowedByReturnStmt();
  void testRedundantDeclarationVariableFollowedByReturnStmtInANestedCompoundStmt();
};
