#include <cxxtest/TestSuite.h>
#include "mo/util/CyclomaticComplexityMeasurement.h"
#include "mo/StringSourceCode.h"

class CyclomaticComplexityMeasurementTest : public CxxTest::TestSuite { 
private:
  CXIndex _index;
  CXTranslationUnit _translationUnit;
  
  void checkCCN(StringSourceCode sourceCode, int expectedCCN);
  
public:
  void setUp();
  void tearDown();
  void testNoDecisionPoint();
  void testOneIfStatement();
  void testOneForStatement();
  void testOneObjCForCollectionStatement();
  void testOneWhileStatement();
  void testOneDoStatement();
  void testOneCaseStatement();
  void testTwoCaseStatements();
  void testOneObjCAtCatchStatement();
  void testOneConditionalOperator();
  void testOneLogicAndOperator();
  void testOneLogicOrOperator();
  void testABinaryOperatorButHasNoEffectOnCCNCouting();
};
