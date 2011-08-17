#ifndef MO_REPORTER_H
#define MO_REPORTER_H

#include <vector>
#include <string>

using namespace std;

#include <clang-c/Index.h>

class Violation;

class Reporter {
public:
  virtual ~Reporter() {}
  
  virtual const string reportDiagnostics(const vector<CXDiagnostic>& diagnostics) const = 0;
  virtual const string reportViolations(const vector<Violation>& violations) const = 0;
};

#endif
