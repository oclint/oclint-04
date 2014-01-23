#ifndef OCLINT_RULE_H
#define OCLINT_RULE_H

#include <string>

#include <clang-c/Index.h>

class ViolationSet;
class RuleSet;

using namespace std;

class Rule
{
public:
  virtual ~Rule()
  {
  }

  virtual void apply(
    CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) = 0;

  virtual const string name() const = 0;
};

#endif
