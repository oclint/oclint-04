#ifndef OCLINT_REPORTER_HTMLREPORTER_H
#define OCLINT_REPORTER_HTMLREPORTER_H

#include "oclint/Reporter.h"

class HTMLReporter : public Reporter {
public:
  virtual const string header() const;
  virtual const string reportDiagnostics(
    const vector<CXDiagnostic>& diagnostics) const;
  virtual const string reportViolations(
    const vector<Violation>& violations) const;
  virtual const string footer() const;
};

#endif
