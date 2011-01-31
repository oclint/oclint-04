#ifndef MO_RULE_RULEVIOLATION_H
#define MO_RULE_RULEVIOLATION_H

#include <string>

using namespace std;

#include <clang/Basic/SourceManager.h>

using namespace clang;

#include "mo/rule/AbstractRule.h"

class RuleViolation {
private:
  SourceRange _sourceRange;
  AbstractRule *_rule;
  string _message;

public:
  RuleViolation(SourceRange sourceRange, AbstractRule *rule, string message = "") {
    _sourceRange = sourceRange;
    _rule = rule;
    _message = message;
  }
  
  SourceRange getSourceRange() {
    return _sourceRange;
  }
  
  AbstractRule *getRule() {
    return _rule;
  }
  
  string getMessage() {
    return _message;
  }
};

#endif
