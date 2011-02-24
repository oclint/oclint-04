#ifndef MO_REPORTER_PLAINTEXTREPORTER_H
#define MO_REPORTER_PLAINTEXTREPORTER_H

#include "mo/Reporter.h"

class PlainTextReporter : public Reporter {
public:
  void reportDiagnostics(vector<CXDiagnostic> diagnostics) const;
  void reportViolations(const vector<RuleViolation> violations) const;
};

#endif
