#include "mo/rule/UnusedMethodParameterRuleTest.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/CursorExtractionUtil.h"

#include <clang/AST/Decl.h>

using namespace clang;

void UnusedMethodParameterRuleTest::setUp() {
  _rule = new UnusedMethodParameterRule();
}

void UnusedMethodParameterRuleTest::tearDown() {
  delete _rule;
}

void UnusedMethodParameterRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "unused method parameter");
}

void UnusedMethodParameterRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated) {
  ViolationSet violationSet;
  _rule->apply(cursorPair.first, cursorPair.second, violationSet);
  if (isViolated) {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
    Violation violation = violationSet.getViolations().at(0);
    TS_ASSERT_EQUALS(violation.rule, _rule);
  }
  else {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
  }
}

void UnusedMethodParameterRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  });
  checkRule(cursorPair, isViolated);
}

void UnusedMethodParameterRuleTest::testMethodWithUsedParameter() {
  checkRule("int aMethod(int a) { a++; return 0; }", false);
}

void UnusedMethodParameterRuleTest::testMethodWithUnusedParameter() {
  checkRule("int aMethod(int a) { return 0; }", true);
}

void UnusedMethodParameterRuleTest::testObjCMethodWithUnusedParameter() {
  string strSource = "@interface AClass\n- (void)aMethod:(int)a;\n@end\n\
    @implementation AClass\n- (void)aMethod:(int)a {}\n@end";
  StringSourceCode strCode(strSource, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  }, -1);
  checkRule(cursorPair, true);
}

void UnusedMethodParameterRuleTest::testFunctionDeclationWithoutDefincationShouldBeIgnored() {
  StringSourceCode strCode("int aMethod(int a);", "c");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  });
  checkRule(cursorPair, false);
}

void UnusedMethodParameterRuleTest::testCppMethodDeclationWithoutDefincationShouldBeIgnored() {
  StringSourceCode strCode("class AClass { int aMethod(int a); };\nint AClass::aMethod(int a) { return 0; }", "cpp");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  });
  checkRule(cursorPair, false);
}

void UnusedMethodParameterRuleTest::testCppMethodInheritanceFromBaseClassShouldBeIgnored() {
  StringSourceCode strCode("\
  class BaseClass { virtual int aMethod(int a); };\n\
  class SubClass : public BaseClass {}\n\
  int SubClass::aMethod(int a) { return 0; }", "cpp");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  }, -1);
  checkRule(cursorPair, false);
}

void UnusedMethodParameterRuleTest::testCppMethodWithoutVirtualInBaseClassIsAViolation() {
  StringSourceCode strCode("\
  class BaseClass { int aMethod(int a); };\n\
  class SubClass : public BaseClass {}\n\
  int SubClass::aMethod(int a) { return 0; }", "cpp");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  }, -1);
  checkRule(cursorPair, true);
}

void UnusedMethodParameterRuleTest::testStaticFunctionShouldBeIgnored() {
  StringSourceCode strCode("\
  class AClass { static string aString; };\n\
  string AClass::aString(\"foo\");", "cpp");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  }, -1);
  checkRule(cursorPair, false);
}

void UnusedMethodParameterRuleTest::testObjCMethodDeclarationInsideInterfaceShouldBeIgnored() {
  checkRule("@interface AnInterface\n- (void)aMethod:(int)a;\n@end", false);
}

void UnusedMethodParameterRuleTest::testObjCMethodDeclarationInsideProtocolShouldBeIgnored() {
  checkRule("@protocol AnInterface\n- (void)aMethod:(int)a;\n@end", false);
}

void UnusedMethodParameterRuleTest::testObjCMethodDeclarationInsideCategoryShouldBeIgnored() {
  checkRule("@interface AnInterface\n@end\n@interface AnInterface (ACategory)\n- (void)aMethod:(int)a;\n@end", false);
}

void UnusedMethodParameterRuleTest::testObjCMethodInheritanceFromBaseInterfaceShouldBeIgnored() {
  StringSourceCode strCode("\
  @interface BaseClass\n- (void)aMethod:(int)a;\n@end\n\
  @interface SubClass : BaseClass\n@end\n\
  @implementation SubClass\n- (void)aMethod:(int)a {}\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  }, -1);
  checkRule(cursorPair, false);
}

void UnusedMethodParameterRuleTest::testObjCMethodImplementedForProtocolShouldBeIgnored() {
  StringSourceCode strCode("\
  @protocol AProtocol\n- (void)aMethod:(int)a;\n@end\n\
  @interface AnInterface <AProtocol>\n@end\n\
  @implementation AnInterface\n- (void)aMethod:(int)a {}\n@end", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  }, -1);
  checkRule(cursorPair, false);
}

void UnusedMethodParameterRuleTest::testUnusedLocalVariableShouldBeIgnoredInThisRule() {
  checkRule("int aMethod() { int a; return 0; }", false);
}
