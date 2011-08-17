#ifndef MO_REPORTER_MOCKREPORTER_H
#define MO_REPORTER_MOCKREPORTER_H

#include "mo/Reporter.h"

class MockReporter : public Reporter {
public:
  virtual const string reportDiagnostics(const vector<CXDiagnostic>& diagnostics) const;
  virtual const string reportViolations(const vector<Violation>& violations) const;
};

#endif
