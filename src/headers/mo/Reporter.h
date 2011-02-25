#ifndef MO_REPORTER_H
#define MO_REPORTER_H

#include <vector>

using namespace std;

#include <clang-c/Index.h>

class RuleViolation;

class Reporter {
public:
  virtual ~Reporter() {}
  
  virtual const string reportDiagnostics(const vector<CXDiagnostic> diagnostics) const = 0;
  virtual void reportViolations(const vector<RuleViolation> violations) const = 0;
};

#endif
