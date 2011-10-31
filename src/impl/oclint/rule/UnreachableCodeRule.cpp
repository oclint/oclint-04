#include "oclint/rule/UnreachableCodeRule.h"
#include "oclint/RuleSet.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/helper/CursorHelper.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/StmtObjC.h>

using namespace clang;

RuleSet UnreachableCodeRule::rules(new UnreachableCodeRule());

bool UnreachableCodeRule::isBreakPoint(Stmt *stmt, CXCursor& parentNode) {
  if (isa<ReturnStmt>(stmt)) {
    return true;
  }
  if (isa<BreakStmt>(stmt) || isa<ContinueStmt>(stmt)) {
    Stmt *parentStmt = CursorHelper::getStmt(parentNode);
    if (isLoopStmt(parentStmt)) {
      return true;
    }
  }
  return false;
}

bool UnreachableCodeRule::isLoopStmt(Stmt *stmt) {
  return isa<ForStmt>(stmt) || isa<ObjCForCollectionStmt>(stmt) || 
    isa<DoStmt>(stmt) || isa<WhileStmt>(stmt);
}

void UnreachableCodeRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorHelper::getStmt(node);
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
          hasBreakPoint = isBreakPoint(bodyStmt, parentNode);
        }
      }
    }
  }
}

const string UnreachableCodeRule::name() const {
  return "unreachable code";
}
