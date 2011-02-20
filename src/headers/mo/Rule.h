#ifndef MO_RULE_H
#define MO_RULE_H

#include <string>

using namespace std;

#include <clang-c/Index.h>

class RuleData;

class Rule {
public:
  virtual ~Rule() {}
  
  virtual void apply(CXCursor node, CXCursor parentNode, RuleData& data) {}

  virtual const string name() = 0;
};

#endif
