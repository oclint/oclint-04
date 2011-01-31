#ifndef MO_RULE_VIOLATION_H
#define MO_RULE_VIOLATION_H

#include <string>
#include <vector>

using namespace std;

#include <clang/Basic/SourceManager.h>
#include <clang/Basic/LangOptions.h>

using namespace clang;

#include "mo/exception/MessageBasedException.h"
#include "mo/rule/RuleViolation.h"
#include "mo/rule/AbstractRule.h"

class Violation {
private:
  vector<RuleViolation*> _violations;

public:
  void addViolation(SourceRange sourceRange, AbstractRule* rule, string message = "");
  void addViolation(RuleViolation *violation);
  int numberOfViolations();
  RuleViolation* violation(int index);

protected:
  bool indexWithinViolationRange(int index);
};

#endif
