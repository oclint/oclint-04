#include "oclint/reporter/HTMLReporter.h"

const string HTMLReporter::reportDiagnostics(const vector<CXDiagnostic>& diagnostics) const {
  return "Sorry, html output is not supported in this version, please check out previous or next version.\n";
}

const string HTMLReporter::reportViolations(const vector<Violation>& violations) const {
  return "Sorry, html output is not supported in this version, please check out previous or next version.\n";
}
