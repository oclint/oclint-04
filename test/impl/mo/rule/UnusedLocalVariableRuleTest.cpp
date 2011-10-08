#include "mo/rule/UnusedLocalVariableRuleTest.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/CursorExtractionUtil.h"

#include <clang/AST/Decl.h>

using namespace clang;

void UnusedLocalVariableRuleTest::setUp() {
  _rule = new UnusedLocalVariableRule();
}

void UnusedLocalVariableRuleTest::tearDown() {
  delete _rule;
}

void UnusedLocalVariableRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "unused local variable");
}

void UnusedLocalVariableRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated) {
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

void UnusedLocalVariableRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  });
  checkRule(cursorPair, isViolated);
}

void UnusedLocalVariableRuleTest::testMethodWithUsedParameter() {
  checkRule("int aMethod(int a) { a++; return 0; }", false);
}

void UnusedLocalVariableRuleTest::testMethodWithUnusedParameter() {
  checkRule("int aMethod(int a) { return 0; }", true);
}

void UnusedLocalVariableRuleTest::testObjCMethodWithUnusedParameter() {
  string strSource = "@interface AClass\n- (void)aMethod:(int)a;\n@end\n\
    @implementation AClass\n- (void)aMethod:(int)a {}\n@end";
  StringSourceCode strCode(strSource, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  }, -1);
  checkRule(cursorPair, true);
}

void UnusedLocalVariableRuleTest::testUsedLocalVariable() {
  checkRule("int aMethod() { int a; a = 1; return 0; }", false);
}

void UnusedLocalVariableRuleTest::testUnusedLocalVariable() {
  checkRule("int aMethod() { int a; return 0; }", true);
}

void UnusedLocalVariableRuleTest::testUnusedLocalVariableWithIntialAssignment() {
  checkRule("int aMethod() { int a = 1; return 0; }", true);
}

void UnusedLocalVariableRuleTest::testFunctionDeclationWithoutDefincationShouldBeIgnored() {
  StringSourceCode strCode("int aMethod(int a);", "c");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  });
  checkRule(cursorPair, false);
}

void UnusedLocalVariableRuleTest::testCppMethodDeclationWithoutDefincationShouldBeIgnored() {
  StringSourceCode strCode("class AClass { int aMethod(int a); };\nint AClass::aMethod(int a) { return 0; }", "cpp");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  });
  checkRule(cursorPair, false);
}

void UnusedLocalVariableRuleTest::testCppMethodInheritanceFromBaseClassShouldBeIgnored() {
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

void UnusedLocalVariableRuleTest::testCppMethodWithoutVirtualInBaseClassIsAViolation() {
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

void UnusedLocalVariableRuleTest::testSaticFunctionShouldBeIgnored() {
  StringSourceCode strCode("\
  class AClass { static string aString; };\n\
  string AClass::aString(\"foo\");", "cpp");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<VarDecl>(decl);
  }, -1);
  checkRule(cursorPair, false);
}

void UnusedLocalVariableRuleTest::testObjCMethodDeclarationInsideInterfaceShouldBeIgnored() {
  checkRule("@interface AnInterface\n- (void)aMethod:(int)a;\n@end", false);
}

void UnusedLocalVariableRuleTest::testObjCMethodDeclarationInsideProtocolShouldBeIgnored() {
  checkRule("@protocol AnInterface\n- (void)aMethod:(int)a;\n@end", false);
}

void UnusedLocalVariableRuleTest::testObjCMethodDeclarationInsideCategoryShouldBeIgnored() {
  checkRule("@interface AnInterface\n@end\n@interface AnInterface (ACategory)\n- (void)aMethod:(int)a;\n@end", false);
}

void UnusedLocalVariableRuleTest::testObjCMethodInheritanceFromBaseInterfaceShouldBeIgnored() {
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

void UnusedLocalVariableRuleTest::testObjCMethodImplementedForProtocolShouldBeIgnored() {
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
