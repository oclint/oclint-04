#include "mo/reporter/PlainTextReporterTest.h"
#include "mo/RuleViolation.h"
#include "mo/rule/MockRule.h"
#include "mo/util/TestCursorUtil.h"

void PlainTextReporterTest::setUp() {
  reporter = new PlainTextReporter();
}

void PlainTextReporterTest::tearDown() {
  delete reporter;
}

void PlainTextReporterTest::testReportDiagnostics() {
  string diagnosticMessage = "test/samples/CompilerDiagnostics.cpp:3:9:{3:7-3:12}: warning: using the result of an assignment as a condition without parentheses [-Wparentheses]\n";
  diagnosticMessage += "test/samples/CompilerDiagnostics.cpp:3:9: note: use '==' to turn this assignment into an equality comparison\n";
  diagnosticMessage += "test/samples/CompilerDiagnostics.cpp:3:9: note: place parentheses around the assignment to silence this warning\n";
  diagnosticMessage += "test/samples/CompilerDiagnostics.cpp:6:11: error: expected ';' after return statement\n";
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, "test/samples/CompilerDiagnostics.cpp", 0, 0, 0, 0, CXTranslationUnit_None);
  vector<CXDiagnostic> diagnostics;
  for (int index = 0, numberOfDiagnostics = clang_getNumDiagnostics(translationUnit); index < numberOfDiagnostics; index++) {
    diagnostics.push_back(clang_getDiagnostic(translationUnit, index));
  }
  TS_ASSERT_EQUALS(reporter->reportDiagnostics(diagnostics), diagnosticMessage);
  clang_disposeTranslationUnit(translationUnit);
  clang_disposeIndex(index);
}

void PlainTextReporterTest::testCursorLocationToPlainText() {
  string cursorLocationPlainText = "test/samples/SwitchStatement.m:3:3";
  CXCursor switchStmtCursor = TestCursorUtil::getSwitchStmtCursor();
  TS_ASSERT_EQUALS(reporter->cursorLocationToPlainText(switchStmtCursor), cursorLocationPlainText);
}

void PlainTextReporterTest::testReportViolations() {
  string violationMessage = "test/samples/SwitchStatement.m:3:3: code smell: mock rule\n";
  violationMessage += "test/samples/SwitchStatement.m:3:3: code smell: mock rule\n";
  RuleViolation violation1(TestCursorUtil::getSwitchStmtCursor(), new MockRule());
  RuleViolation violation2(TestCursorUtil::getSwitchStmtCursor(), new MockRule());
  vector<RuleViolation> violations;
  violations.push_back(violation1);
  violations.push_back(violation2);
  TS_ASSERT_EQUALS(reporter->reportViolations(violations), violationMessage);
}
