#include "oclint/reporter/HTMLReporterTest.h"
#include "oclint/Violation.h"
#include "oclint/rule/MockRule.h"
#include "oclint/StringSourceCode.h"
#include "oclint/helper/StringSourceCodeToTranslationUnitHelper.h"
#include "oclint/helper/CursorExtractionHelper.h"
#include "oclint/helper/CursorHelper.h"
#include "oclint/Version.h"

#include <clang/AST/Stmt.h>

using namespace std;

void HTMLReporterTest::setUp() {
  _reporter = new HTMLReporter();
}

void HTMLReporterTest::tearDown() {
  delete _reporter;
}

void HTMLReporterTest::testHeader() {
  TS_ASSERT_EQUALS(_reporter->header(), "<html>\n<head>\n<title>OCLint Report</title>\n</head>\n<body>\n<h1>OCLint Report</h1>\n<ul>\n\
    <table><tr><td>Rule Name</td><td>File Name</td><td>Line</td><td>Column</td><td>Description</td></tr>");
}

void HTMLReporterTest::testFooter() {
  TS_ASSERT_EQUALS(_reporter->footer(), "</table></ul>\n<p><a href=\"http://oclint.org\">OCLint</a> v" + oclint_version() + "</p>\n</body>\n</html>\n");
}

void HTMLReporterTest::testReportDiagnostics() {
  StringSourceCode strCode("int main() { return 0 }", "cpp");
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = StringSourceCodeToTranslationUnitHelper::compileStringSourceCodeToTranslationUnit(strCode, index);
  int tmpFileNameLength = StringSourceCodeToTranslationUnitHelper::lengthOfTmpFileName(strCode);
  vector<CXDiagnostic> diagnostics;
  for (int idx = 0, numberOfDiagnostics = clang_getNumDiagnostics(translationUnit); idx < numberOfDiagnostics; idx++) {
    diagnostics.push_back(clang_getDiagnostic(translationUnit, idx));
  }
  TS_ASSERT_EQUALS(_reporter->reportDiagnostics(diagnostics), "");
}

void HTMLReporterTest::testReportEmptyDiagnostics() {
  string diagnosticMessage;
  vector<CXDiagnostic> diagnostics;
  TS_ASSERT_EQUALS(_reporter->reportDiagnostics(diagnostics), diagnosticMessage);
}

void HTMLReporterTest::testReportViolations() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorHelper::getStmt(node);
    return stmt && isa<SwitchStmt>(stmt);
  });
  int tmpFileNameLength = StringSourceCodeToTranslationUnitHelper::lengthOfTmpFileName(strCode);
  Violation violation(cursorPair.first, new MockRule());
  vector<Violation> violations;
  violations.push_back(violation);
  string violationMessageFirst = "<tr><td>mock rule</td><td>";
  string violationMessageSecond = "</td><td>1</td><td>25</td><td></td></tr>\n";
  TS_ASSERT_EQUALS(_reporter->reportViolations(violations).substr(0, violationMessageFirst.length()), violationMessageFirst);
  TS_ASSERT_EQUALS(_reporter->reportViolations(violations).substr(violationMessageFirst.length() + tmpFileNameLength), violationMessageSecond);
}

void HTMLReporterTest::testReportViolationsWithDescription() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorHelper::getStmt(node);
    return stmt && isa<SwitchStmt>(stmt);
  });
  int tmpFileNameLength = StringSourceCodeToTranslationUnitHelper::lengthOfTmpFileName(strCode);
  Violation violation(cursorPair.first, new MockRule(), "violation description");
  vector<Violation> violations;
  violations.push_back(violation);
  string violationMessageFirst = "<tr><td>mock rule</td><td>";
  string violationMessageSecond = "</td><td>1</td><td>25</td><td>violation description</td></tr>\n";
  TS_ASSERT_EQUALS(_reporter->reportViolations(violations).substr(0, violationMessageFirst.length()), violationMessageFirst);
  TS_ASSERT_EQUALS(_reporter->reportViolations(violations).substr(violationMessageFirst.length() + tmpFileNameLength), violationMessageSecond);
}

void HTMLReporterTest::testReportEmptyViolations() {
  string violationMessage;
  vector<Violation> violations;
  TS_ASSERT_EQUALS(_reporter->reportViolations(violations), violationMessage);
}
