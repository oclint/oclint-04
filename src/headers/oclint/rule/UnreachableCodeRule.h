#ifndef OCLINT_RULE_UNREACHABLECODERULE_H
#define OCLINT_RULE_UNREACHABLECODERULE_H

#include "oclint/Rule.h"

namespace clang {
  class Stmt;
}

class UnreachableCodeRule : public Rule {
private:
  static RuleSet rules;
  
  bool isBreakPoint(clang::Stmt *stmt, CXCursor& parentNode);
  bool isLoopStmt(clang::Stmt *stmt);
  
public:
  virtual void apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet);
  virtual const string name() const;
};

#endif
