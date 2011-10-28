#include "oclint/Violation.h"
#include "oclint/Rule.h"
#include "oclint/reporter/PlainTextReporter.h"
#include "oclint/util/CursorUtil.h"

#include <sstream> // Think about it

const string PlainTextReporter::header() const {
  return "OCLint Report:\n\n";
}

const string PlainTextReporter::footer() const {
  return "\n[OCLint (http://oclint.org) v0.2.6]\n";
}

const string PlainTextReporter::reportDiagnostics(const vector<CXDiagnostic>& diagnostics) const {
  string formatedDiagnostics;
  unsigned displayOptions = CXDiagnostic_DisplaySourceLocation
    | CXDiagnostic_DisplayColumn | CXDiagnostic_DisplaySourceRanges
    | CXDiagnostic_DisplayOption;
  for (int index = 0, numberOfDiagnostics = diagnostics.size(); index < numberOfDiagnostics; index++) {
    CXString diagnostic = clang_formatDiagnostic(diagnostics.at(index), displayOptions);
    formatedDiagnostics += clang_getCString(diagnostic);
    formatedDiagnostics += '\n';
    clang_disposeString(diagnostic);
  }
  return formatedDiagnostics;
}

const string PlainTextReporter::reportViolations(const vector<Violation>& violations) const {
  string formatedViolations;
  for (int index = 0, numberOfViolations = violations.size(); index < numberOfViolations; index++) {
    Violation violation = violations.at(index);
    formatedViolations += cursorLocationToPlainText(violation.cursor);
    formatedViolations += ": oclint: " + violation.rule->name();
    formatedViolations += '\n';
  }
  return formatedViolations;
}

const string PlainTextReporter::cursorLocationToPlainText(const CXCursor& cursor) const {
  return CursorUtil::getFileName(cursor) + ":" + CursorUtil::getLineNumber(cursor) + ":" + CursorUtil::getColumnNumber(cursor);
}
