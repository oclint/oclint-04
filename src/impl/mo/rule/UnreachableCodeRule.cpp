#include "mo/rule/UnreachableCodeRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

RuleSet UnreachableCodeRule::rules(new UnreachableCodeRule());

void UnreachableCodeRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorUtil::getStmt(node);
  if (stmt) {
    CompoundStmt *compoundStmt = dyn_cast<CompoundStmt>(stmt);
    if (compoundStmt) {
      bool hasBreakPoint = false;
      for (CompoundStmt::body_iterator body = compoundStmt->body_begin(), bodyEnd = compoundStmt->body_end(); body != bodyEnd; body++) {
        if (hasBreakPoint) {
          Violation violation(node, this);
          violationSet.addViolation(violation);
          return;
        }
        else {
          Stmt *bodyStmt = (Stmt *)*body;
          if (isa<ReturnStmt>(bodyStmt)) {
            hasBreakPoint = true;
          }
          if (isa<BreakStmt>(bodyStmt)) {
            Stmt *parentStmt = CursorUtil::getStmt(parentNode);
            if (isa<ForStmt>(parentStmt)) {
              hasBreakPoint = true;
            }
          }
        }
      }
    }
  }
}

const string UnreachableCodeRule::name() const {
  return "unreachable code";
}
