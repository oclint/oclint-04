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
};
