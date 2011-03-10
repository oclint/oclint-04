#ifndef MO_RULE_H
#define MO_RULE_H

#include <string>

using namespace std;

#include <clang-c/Index.h>

class RuleData;

class Rule {
public:
  virtual ~Rule() {}
  
  virtual void apply(CXCursor& node, CXCursor& parentNode, RuleData& data) = 0;

  virtual const string name() const = 0;
};

#endif
