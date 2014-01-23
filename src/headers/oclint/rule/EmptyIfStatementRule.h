#ifndef OCLINT_RULE_EMPTYIFSTATEMENTRULE_H
#define OCLINT_RULE_EMPTYIFSTATEMENTRULE_H

#include "oclint/Rule.h"

namespace clang
{
  class Stmt;
}

class EmptyIfStatementRule : public Rule
{
private:
  static RuleSet rules;

  bool isLexicalEmpty(clang::Stmt *stmt);

public:
  virtual void apply(
    CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
