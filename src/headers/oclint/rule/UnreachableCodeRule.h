#ifndef OCLINT_RULE_UNREACHABLECODERULE_H
#define OCLINT_RULE_UNREACHABLECODERULE_H

#include "oclint/Rule.h"

namespace clang {
  class Stmt;
}

using namespace clang;

class UnreachableCodeRule : public Rule {
private:
  static RuleSet rules;
  
  bool isBreakPoint(Stmt *stmt, CXCursor& parentNode);
  bool isLoopStmt(Stmt *stmt);
  bool isBreakOrContinueInLoopStatement(Stmt *stmt, CXCursor& parentNode);
  
public:
  virtual void apply(
    CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
