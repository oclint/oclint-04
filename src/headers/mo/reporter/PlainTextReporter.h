#ifndef MO_REPORTER_PLAINTEXTREPORTER_H
#define MO_REPORTER_PLAINTEXTREPORTER_H

#include "mo/Reporter.h"

class PlainTextReporter : public Reporter {
public:
  virtual const string reportDiagnostics(const vector<CXDiagnostic>& diagnostics) const;
  virtual const string reportViolations(const vector<RuleViolation>& violations) const;
  
  const string cursorLocationToPlainText(const CXCursor& cursor) const;
};

#endif
