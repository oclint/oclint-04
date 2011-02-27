#include "mo/reporter/MockReporter.h"

const string MockReporter::reportDiagnostics(const vector<CXDiagnostic> diagnostics) const {
  return "mock report diagnostics";
}

const string MockReporter::reportViolations(const vector<RuleViolation> violations) const {
  return "mock report violations";
}
