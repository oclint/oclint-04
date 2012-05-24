#ifndef OCLINT_REPORTER_H
#define OCLINT_REPORTER_H

#include <vector>
#include <string>

#include <clang-c/Index.h>

class Violation;

using namespace std;

class Reporter {
public:
  virtual ~Reporter() {}
  
  virtual const string header() const = 0;
  virtual const string reportDiagnostics(const vector<CXDiagnostic>& diagnostics) const = 0;
  virtual const string reportViolations(const vector<Violation>& violations) const = 0;
  virtual const string footer() const = 0;
};

#endif
