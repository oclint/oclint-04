#ifndef MO_REPORTER_PLAINTEXTREPORTER_H
#define MO_REPORTER_PLAINTEXTREPORTER_H

#include "mo/Reporter.h"

class PlainTextReporter : public Reporter {
public:
  const string reportDiagnostics(const vector<CXDiagnostic> diagnostics) const;
  const string reportViolations(const vector<RuleViolation> violations) const;
  
  const string cursorLocationToPlainText(CXCursor cursor) const;
};

#endif
