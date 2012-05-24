#ifndef OCLINT_REPORTER_PLAINTEXTREPORTER_H
#define OCLINT_REPORTER_PLAINTEXTREPORTER_H

#include "oclint/Reporter.h"

class PlainTextReporter : public Reporter {
private:  
  const string cursorLocationToPlainText(const CXCursor& cursor) const;
  
public:
  virtual const string header() const;
  virtual const string reportDiagnostics(
    const vector<CXDiagnostic>& diagnostics) const;
  virtual const string reportViolations(
    const vector<Violation>& violations) const;
  virtual const string footer() const;
};

#endif
