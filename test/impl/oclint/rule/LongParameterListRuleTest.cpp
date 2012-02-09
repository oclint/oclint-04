#include "oclint/rule/LongParameterListRuleTest.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/StringSourceCode.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/CursorExtractionHelper.h"

#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>

using namespace clang;

void LongParameterListRuleTest::setUp() {
  _rule = new LongParameterListRule();
}

void LongParameterListRuleTest::tearDown() {
  delete _rule;
}

void LongParameterListRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "long parameter list");
}

void LongParameterListRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated, string description) {
  ViolationSet violationSet;
  _rule->apply(cursorPair.first, cursorPair.second, violationSet);
  if (isViolated) {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
    Violation violation = violationSet.getViolations().at(0);
    TS_ASSERT_EQUALS(violation.rule, _rule);
    TS_ASSERT_EQUALS(violation.description, description);
  }
  else {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
  }
}

void LongParameterListRuleTest::checkRule(string source, string sourcetype, bool isViolated, string description) {
  StringSourceCode strCode(source, sourcetype);
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    if (decl) {
      if (sourcetype == "m") {
        return isa<ObjCMethodDecl>(decl);
      }
      else {
        return isa<FunctionDecl>(decl);
      }
    }
    return false;
  }, -1);
  checkRule(cursorPair, isViolated, description);
}

void LongParameterListRuleTest::testObjCMethodWithThreeParametersIsNotASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithThreeParameters:(int)param1 param2:(int)param2 param3:(int)param3 {}\n@end";
  checkRule(strSource, "m", false, "");
}

void LongParameterListRuleTest::testObjCMethodWithFourParametersIsASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithFourParameters:(int)param1 param2:(int)param2 param3:(int)param3 param4:(int)param4 {}\n@end";
  checkRule(strSource, "m", true, "Method of 4 parameters exceeds limit of 3.");
}

void LongParameterListRuleTest::testObjCMethodWithFiveParametersIsASmell() {
  string strSource = "@implementation ClassName\n- (void)aMethodWithFiveParameters:(int)param1 param2:(int)param2 param3:(int)param3 param4:(int)param4 param5:(int)param5, ... {}\n@end";
  checkRule(strSource, "m", true, "Method of 5 parameters exceeds limit of 3.");
}

void LongParameterListRuleTest::testObjCMethodDeclaredInSuperClassShouldBeIgnored() {
  string strSource = "\
  @interface BaseClass\n- (void)aMethodWithFourParameters:(int)param1 param2:(int)param2 param3:(int)param3 param4:(int)param4;\n@end\n\
  @interface SubClass : BaseClass\n@end\n\
  @implementation SubClass\n- (void)aMethodWithFourParameters:(int)param1 param2:(int)param2 param3:(int)param3 param4:(int)param4 {}\n@end";
  checkRule(strSource, "m", false, "");
}

void LongParameterListRuleTest::testObjCMethodDeclaredInProtocolShouldBeIgnored() {
  string strSource = "\
  @protocol AProtocol\n- (void)aMethodWithFourParameters:(int)param1 param2:(int)param2 param3:(int)param3 param4:(int)param4;\n@end\n\
  @interface ClassName <AProtocol>\n@end\n\
  @implementation ClassName\n- (void)aMethodWithFourParameters:(int)param1 param2:(int)param2 param3:(int)param3 param4:(int)param4 {}\n@end";
  checkRule(strSource, "m", false, "");
}

void LongParameterListRuleTest::testCppMethodWithThreeParametersIsNotASmell() {
  string strSource = "int aMethod(int a, int b, int c) {}";
  checkRule(strSource, "cpp", false, "");
}

void LongParameterListRuleTest::testCppMethodWithFourParametersIsASmell() {
  string strSource = "int aMethod(int a, int b, int c, int d) {}";
  checkRule(strSource, "cpp", true, "Method of 4 parameters exceeds limit of 3.");
}

void LongParameterListRuleTest::testCppMethodWithFiveParametersIsASmell() {
  string strSource = "int aMethod(int a, int b, int c, int d, int e) {}";
  checkRule(strSource, "cpp", true, "Method of 5 parameters exceeds limit of 3.");
}
