#include "mo/reporter/PlainTextReporterTest.h"
#include "mo/Violation.h"
#include "mo/rule/MockRule.h"
#include "mo/util/TestCursorUtil.h"
#include "mo/StringSourceCode.h"
#include "mo/util/StringSourceCodeToTranslationUnitUtil.h"

void PlainTextReporterTest::setUp() {
  _reporter = new PlainTextReporter();
}

void PlainTextReporterTest::tearDown() {
  delete _reporter;
}

void PlainTextReporterTest::testReportDiagnostics() {
  StringSourceCode strCode("int main() { return 0 }", "cpp");
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(strCode, index);
  int tmpFileNameLength = StringSourceCodeToTranslationUnitUtil::lengthOfTmpFileName(strCode);
  vector<CXDiagnostic> diagnostics;
  for (int idx = 0, numberOfDiagnostics = clang_getNumDiagnostics(translationUnit); idx < numberOfDiagnostics; idx++) {
    diagnostics.push_back(clang_getDiagnostic(translationUnit, idx));
  }
  string diagnosticMessage = ":1:22: error: expected ';' after return statement\n";
  TS_ASSERT_EQUALS(_reporter->reportDiagnostics(diagnostics).substr(tmpFileNameLength), diagnosticMessage);
}

void PlainTextReporterTest::testReportEmptyDiagnostics() {
  string diagnosticMessage;
  vector<CXDiagnostic> diagnostics;
  TS_ASSERT_EQUALS(_reporter->reportDiagnostics(diagnostics), diagnosticMessage);
}

void PlainTextReporterTest::testCursorLocationToPlainText() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  CXCursor switchStmtCursor = TestCursorUtil::getSwitchStmtCursor(strCode);
  int tmpFileNameLength = StringSourceCodeToTranslationUnitUtil::lengthOfTmpFileName(strCode);
  string cursorLocationPlainText = ":1:25";
  string reportString = _reporter->cursorLocationToPlainText(switchStmtCursor);
  TS_ASSERT_EQUALS(reportString.substr(tmpFileNameLength), cursorLocationPlainText);
}

void PlainTextReporterTest::testReportViolations() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  CXCursor switchStmtCursor = TestCursorUtil::getSwitchStmtCursor(strCode);
  int tmpFileNameLength = StringSourceCodeToTranslationUnitUtil::lengthOfTmpFileName(strCode);
  Violation violation(switchStmtCursor, new MockRule());
  vector<Violation> violations;
  violations.push_back(violation); 
  string violationMessage = ":1:25: code smell: mock rule\n";
  TS_ASSERT_EQUALS(_reporter->reportViolations(violations).substr(tmpFileNameLength), violationMessage);
}

void PlainTextReporterTest::testReportEmptyViolations() {
  string violationMessage;
  vector<Violation> violations;  
  TS_ASSERT_EQUALS(_reporter->reportViolations(violations), violationMessage);
}
