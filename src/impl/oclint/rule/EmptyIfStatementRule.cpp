#include "oclint/rule/EmptyIfStatementRule.h"
#include "oclint/RuleSet.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/util/CursorUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

RuleSet EmptyIfStatementRule::rules(new EmptyIfStatementRule());

bool EmptyIfStatementRule::isLexicalEmpty(Stmt *stmt) {
  if (stmt) {
    CompoundStmt *compoundStmt = dyn_cast<CompoundStmt>(stmt);
    return isa<NullStmt>(stmt) || (compoundStmt && compoundStmt->body_empty());
  }
  return false;
}

void EmptyIfStatementRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorUtil::getStmt(node);
  if (stmt) {
    IfStmt *ifStmt = dyn_cast<IfStmt>(stmt);
    if (ifStmt && (isLexicalEmpty(ifStmt->getThen()) || isLexicalEmpty(ifStmt->getElse()))) {
      Violation violation(node, this);
      violationSet.addViolation(violation);
    }
  }
}

const string EmptyIfStatementRule::name() const {
  return "empty if statement";
}
