#include "mo/rule/EmptyIfStatementRule.h"
#include "mo/RuleSet.h"
#include "mo/RuleData.h"
#include "mo/RuleViolation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

RuleSet EmptyIfStatementRule::rules(new EmptyIfStatementRule());

void EmptyIfStatementRule::apply(CXCursor& node, CXCursor& parentNode, RuleData& data) {
  if (Stmt *stmt = CursorUtil::getStmt(node)) {
    if (IfStmt *ifStmt = dyn_cast<IfStmt>(stmt)) {
      if (CompoundStmt *compoundStmt = dyn_cast<CompoundStmt>(ifStmt->getThen())) {
        if (compoundStmt->body_empty()) {
          RuleViolation violation(node, this);
          data.addViolation(violation);
        }
      }
      else {
        if (isa<NullStmt>(ifStmt->getThen())) {
          RuleViolation violation(node, this);
          data.addViolation(violation);
        }
      }
    }
  }
}

const string EmptyIfStatementRule::name() const {
  return "empty if statement";
}
