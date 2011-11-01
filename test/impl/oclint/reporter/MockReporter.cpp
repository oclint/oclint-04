#include "oclint/reporter/MockReporter.h"

const string MockReporter::header() const {
  return "mock report header";
}

const string MockReporter::footer() const {
  return "mock report footer";
}

const string MockReporter::reportDiagnostics(const vector<CXDiagnostic>& diagnostics) const {
  return "mock report diagnostics";
}

const string MockReporter::reportViolations(const vector<Violation>& violations) const {
  return "mock report violations";
}
