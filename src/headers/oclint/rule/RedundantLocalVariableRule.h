#ifndef OCLINT_RULE_REDUNDANTLOCALVARIABLERULE_H
#define OCLINT_RULE_REDUNDANTLOCALVARIABLERULE_H

#include "oclint/Rule.h"

namespace clang
{
  class NamedDecl;
  class Stmt;
}

using namespace clang;

class RedundantLocalVariableRule : public Rule
{
private:
  static RuleSet rules;

  NamedDecl* extractFromReturnStmt(Stmt *stmt);
  NamedDecl* extractFromDeclStmt(Stmt *stmt);

public:
  virtual void apply(
    CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
