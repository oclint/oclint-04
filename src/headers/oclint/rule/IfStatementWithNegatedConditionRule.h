#ifndef OCLINT_RULE_IFSTATEMENTWITHNEGATEDCONDITIONRULE_H
#define OCLINT_RULE_IFSTATEMENTWITHNEGATEDCONDITIONRULE_H

#include "oclint/Rule.h"

namespace clang
{
  class IfStmt;
}

class IfStatementWithNegatedConditionRule : public Rule
{
private:
  static RuleSet rules;

  bool hasElseBlock(clang::IfStmt *ifStmt);
  bool hasNegatedCondition(clang::IfStmt *ifStmt);

public:
  virtual void apply(
    CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
