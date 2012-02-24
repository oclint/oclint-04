#include "oclint/reporter/PlainTextReporterTest.h"
#include "oclint/Violation.h"
#include "oclint/rule/MockRule.h"
#include "oclint/StringSourceCode.h"
#include "oclint/helper/StringSourceCodeToTranslationUnitHelper.h"
#include "oclint/helper/CursorExtractionHelper.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/Version.h"

#include <clang/AST/Stmt.h>

using namespace std;

void PlainTextReporterTest::setUp() {
  _reporter = new PlainTextReporter();
}

void PlainTextReporterTest::tearDown() {
  delete _reporter;
}

void PlainTextReporterTest::testHeader() {
  TS_ASSERT_EQUALS(_reporter->header(), "OCLint Report:\n\n");
}

void PlainTextReporterTest::testFooter() {
  TS_ASSERT_EQUALS(_reporter->footer(), "\n[OCLint (http://oclint.org) v" + oclint_version() + "]\n");
}

void PlainTextReporterTest::testReportDiagnostics() {
  StringSourceCode strCode("int main() { return 0 }", "cpp");
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = StringSourceCodeToTranslationUnitHelper::compileStringSourceCodeToTranslationUnit(strCode, index);
  int tmpFileNameLength = StringSourceCodeToTranslationUnitHelper::lengthOfTmpFileName(strCode);
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

void PlainTextReporterTest::testReportViolations() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorHelper::getStmt(node);
    return stmt && isa<SwitchStmt>(stmt);
  });
  int tmpFileNameLength = StringSourceCodeToTranslationUnitHelper::lengthOfTmpFileName(strCode);
  Violation violation(cursorPair.first, new MockRule());
  vector<Violation> violations;
  violations.push_back(violation);
  string violationMessage = ":1:25: oclint: mock rule\n";
  TS_ASSERT_EQUALS(_reporter->reportViolations(violations).substr(tmpFileNameLength), violationMessage);
}

void PlainTextReporterTest::testReportViolationsWithDescription() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorHelper::getStmt(node);
    return stmt && isa<SwitchStmt>(stmt);
  });
  int tmpFileNameLength = StringSourceCodeToTranslationUnitHelper::lengthOfTmpFileName(strCode);
  Violation violation(cursorPair.first, new MockRule(), "violation description");
  vector<Violation> violations;
  violations.push_back(violation);
  string violationMessage = ":1:25: oclint: violation description\n";
  TS_ASSERT_EQUALS(_reporter->reportViolations(violations).substr(tmpFileNameLength), violationMessage);
}

void PlainTextReporterTest::testReportEmptyViolations() {
  string violationMessage;
  vector<Violation> violations;
  TS_ASSERT_EQUALS(_reporter->reportViolations(violations), violationMessage);
}
