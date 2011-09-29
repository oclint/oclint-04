#include <cxxtest/TestSuite.h>
#include "mo/rule/UnreachableCodeRule.h"

class UnreachableCodeRuleTest : public CxxTest::TestSuite { 
private:
  UnreachableCodeRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRuleOnFunctionRootComponent(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testGoodCompoundStmtWithoutReturnStmt();
  void testGoodCompoundStmtWithReturnStmtAtLastLine();
  void testUnreachableCodeAfterReturnStatement();
  void testUnreachableCodeAfterBreakStatement();
};
