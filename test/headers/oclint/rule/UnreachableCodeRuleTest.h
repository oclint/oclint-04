#include <cxxtest/TestSuite.h>
#include "oclint/rule/UnreachableCodeRule.h"

class UnreachableCodeRuleTest : public CxxTest::TestSuite { 
private:
  UnreachableCodeRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRuleOnFunctionRootComponent(string source, bool isViolated);
  template<typename nodeType, typename parentNodeType> 
  void checkRuleOn(string source, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testGoodCompoundStmtWithoutReturnStmt();
  void testGoodCompoundStmtWithReturnStmtAtLastLine();
  void testCodeAfterReturnStatement();
  void testCodeAfterBreakStatementInForStatement();
  void testCodeAfterContinueStatementInForStatement();
  void testCodeAfterReturnStatementInForStatement();
  void testCodeAfterBreakStatementInObjCForCollectionStatement();
  void testCodeAfterContinueStatementInObjCForCollectionStatement();
  void testCodeAfterReturnStatementInObjCForCollectionStatement();
  void testCodeAfterBreakStatementInWhileStatement();
  void testCodeAfterContinueStatementInWhileStatement();
  void testCodeAfterReturnStatementInWhileStatement();
  void testCodeAfterBreakStatementInDoWhileStatement();
  void testCodeAfterContinueStatementInDoWhileStatement();
  void testCodeAfterReturnStatementInDoWhileStatement();
};
