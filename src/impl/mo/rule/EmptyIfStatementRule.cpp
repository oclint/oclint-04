#include "mo/rule/EmptyIfStatementRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

RuleSet EmptyIfStatementRule::rules(new EmptyIfStatementRule());

void EmptyIfStatementRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorUtil::getStmt(node);
  if (stmt) {
    IfStmt *ifStmt = dyn_cast<IfStmt>(stmt);
    if (ifStmt) {
      CompoundStmt *compoundStmt = dyn_cast<CompoundStmt>(ifStmt->getThen());
      if (compoundStmt) {
        if (compoundStmt->body_empty()) {
          Violation violation(node, this);
          violationSet.addViolation(violation);
        }
      }
      else {
        if (isa<NullStmt>(ifStmt->getThen())) {
          Violation violation(node, this);
          violationSet.addViolation(violation);
        }
      }
    }
  }
}

const string EmptyIfStatementRule::name() const {
  return "empty if statement";
}
