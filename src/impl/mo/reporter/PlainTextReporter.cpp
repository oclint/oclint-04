#include "mo/RuleViolation.h"
#include "mo/reporter/PlainTextReporter.h"

#include <iostream>

void PlainTextReporter::reportDiagnostics(vector<CXDiagnostic> diagnostics) const {
  unsigned displayOptions = CXDiagnostic_DisplaySourceLocation
    | CXDiagnostic_DisplayColumn | CXDiagnostic_DisplaySourceRanges
    | CXDiagnostic_DisplayOption;
  for (int index = 0, numberOfDiagnostics = diagnostics.size(); index < numberOfDiagnostics; index++) {
    CXString diagnostic = clang_formatDiagnostic(diagnostics.at(index), displayOptions);
    cout << clang_getCString(diagnostic) << endl;
    clang_disposeString(diagnostic);
  }
}

void PlainTextReporter::reportViolations(vector<RuleViolation> violations) const {
  cout << "Smell Detected!" << endl;
}
