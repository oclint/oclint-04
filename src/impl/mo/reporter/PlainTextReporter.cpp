#include "mo/RuleViolation.h"
#include "mo/Rule.h"
#include "mo/reporter/PlainTextReporter.h"

#include <iostream>

const string PlainTextReporter::reportDiagnostics(const vector<CXDiagnostic> diagnostics) const {
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

void PlainTextReporter::reportViolations(const vector<RuleViolation> violations) const {
  for (int index = 0, numberOfViolations = violations.size(); index < numberOfViolations; index++) {
    RuleViolation violation = violations.at(index);
    
    CXSourceLocation violatedSourceLocation = clang_getCursorLocation(violation.cursor);
    CXFile file;
    unsigned line, column;
    clang_getSpellingLocation(violatedSourceLocation, &file, &line, &column, 0);
    CXString violatedFile = clang_getFileName(file);
    
    cout << clang_getCString(violatedFile) << ":" << line << ":" << column << ": "
      << "code smell: " << violation.rule->name() << endl;
    clang_disposeString(violatedFile);
  }
}
