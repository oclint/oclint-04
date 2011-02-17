#ifndef MO_RULE_H
#define MO_RULE_H

#include <string>

using namespace std;

#include <clang-c/Index.h>

class RuleViolation;

class Rule {
public:
  virtual ~Rule() {}
  
  virtual void apply(CXCursor node, CXCursor parentNode, RuleViolation *violation) {}

  virtual string name() = 0;
};

#endif
