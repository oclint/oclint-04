#ifndef MO_MOCKREPORTER_H
#define MO_MOCKREPORTER_H

#include "mo/Reporter.h"

class MockReporter : public Reporter {
public:
  const string reportDiagnostics(const vector<CXDiagnostic>& diagnostics) const;
  const string reportViolations(const vector<RuleViolation>& violations) const;
};

#endif
