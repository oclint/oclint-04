#ifndef OCLINT_REPORTER_PLAINTEXTREPORTER_H
#define OCLINT_REPORTER_PLAINTEXTREPORTER_H

#include "oclint/Reporter.h"

class PlainTextReporter : public Reporter {
public:
  virtual const string reportDiagnostics(const vector<CXDiagnostic>& diagnostics) const;
  virtual const string reportViolations(const vector<Violation>& violations) const;
  
  const string cursorLocationToPlainText(const CXCursor& cursor) const;
};

#endif
