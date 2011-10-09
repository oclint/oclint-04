#ifndef MO_RULE_UNREACHABLECODERULE_H
#define MO_RULE_UNREACHABLECODERULE_H

#include "mo/Rule.h"

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
