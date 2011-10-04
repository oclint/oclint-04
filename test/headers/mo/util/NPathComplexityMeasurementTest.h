#include <cxxtest/TestSuite.h>
#include "mo/util/NPathComplexityMeasurement.h"
#include "mo/StringSourceCode.h"

class NPathComplexityMeasurementTest : public CxxTest::TestSuite { 
private:
  void checkNPath(string sourceCode, int expectedNPath);
  
public:
  void testEmptyMethod();
  void testIfStatementWithConstantConditionAndEmptyThenCompoundStmt();
  void testIfStatementWithOneLogicAndOperatorConditionAndEmptyThenCompoundStmt();
  void testIfStatementWithOneLogicOrOperatorConditionAndEmptyThenCompoundStmt();
  void testIfStatementWithMultipleLogicAndOrOperatorsConditionAndEmptyThenCompoundStmt();
  void testIfElseStatementWithConstantConditionAndEmptyThenCompoundStmt();
  void testIfElseStatementWithOneLogicAndOperatorConditionAndEmptyThenCompoundStmt();
  void testIfElseStatementWithOneLogicOrOperatorConditionAndEmptyThenCompoundStmt();
  void testIfElseStatementWithMultipleLogicAndOrOperatorsConditionAndEmptyThenCompoundStmt();
  void testNestedIfStatement();
  void testNestedIfElseStatement();
  void testWhileStatementWithConstantConditionAndEmptyCompoundStmt();
  void testWhileStatementWithOneLogicAndOperatorConditionAndEmptyCompoundStmt();
  void testWhileStatementWithOneLogicOrOperatorConditionAndEmptyCompoundStmt();
  void testDoWhileStatementWithConstantConditionAndEmptyCompoundStmt();
  void testDoWhileStatementWithOneLogicAndOperatorConditionAndEmptyCompoundStmt();
  void testDoWhileStatementWithOneLogicOrOperatorConditionAndEmptyCompoundStmt();
  void testForStatementWithSimpleConditionAndEmptyCompoundStmt();
  void testForStatementWithOneLogicAndOperatorConditionAndEmptyCompoundStmt();
  void testSwitchStatementWithSimpleConditionAndEmptyBody();
  void testSwitchStatementWithSimpleConditionAndOneCase();
  void testSwitchStatementWithSimpleConditionAndOneCaseOneDefault();
  void testSwitchStatementWithSimpleConditionAndTwoCasesOneDefault();
  void testSwitchStatementWithOneLogicAndOperatorConditionAndTwoCasesOneDefault();
  void testSwitchStatementWithSimpleConditionAndOneCaseOneIfOneDefault();
  void testSwitchStatementWithSimpleConditionAndOneCaseAsIfOneDefault();
  void testSwitchStatementWithSimpleConditionAndOneCaseAsTwoIfsOneDefault();
};
