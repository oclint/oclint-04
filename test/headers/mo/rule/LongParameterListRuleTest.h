#include <cxxtest/TestSuite.h>
#include "mo/rule/LongParameterListRule.h"

class LongParameterListRuleTest : public CxxTest::TestSuite { 
private:
  LongParameterListRule *_rule;
  
  void checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated);
  void checkRule(string source, string sourcetype, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testObjCMethodWithThreeParametersIsNotASmell();
  void testObjCMethodWithFourParametersIsASmell();
  void testObjCMethodWithFiveParametersIsASmell();
  void testObjCMethodDeclaredInSuperClassShouldBeIgnored();
  void testObjCMethodDeclaredInProtocolShouldBeIgnored();
  void testCppMethodWithThreeParametersIsNotASmell();
  void testCppMethodWithFourParametersIsASmell();
  void testCppMethodWithFiveParametersIsASmell();
};
