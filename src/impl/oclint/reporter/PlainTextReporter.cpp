#include "oclint/Violation.h"
#include "oclint/Rule.h"
#include "oclint/reporter/PlainTextReporter.h"

#include <sstream> // Think about it

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
  stringstream locationStream;
  CXFile file;
  unsigned line, column;
  clang_getSpellingLocation(clang_getCursorLocation(cursor), &file, &line, &column, 0);
  CXString violatedFile = clang_getFileName(file);
  locationStream << clang_getCString(violatedFile) << ":" << line << ":" << column;
  clang_disposeString(violatedFile);
  return locationStream.str();
}
