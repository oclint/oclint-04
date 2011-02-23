#include "mo/RuleViolation.h"
#include "mo/reporter/PlainTextReporter.h"

#include <iostream>

void PlainTextReporter::reportDiagnostics(vector<CXDiagnostic> diagnostics) const {
  cout << "Diagnostics Detected!" << endl;
}

void PlainTextReporter::reportViolations(vector<RuleViolation> violations) const {
  cout << "Smell Detected!" << endl;
}
