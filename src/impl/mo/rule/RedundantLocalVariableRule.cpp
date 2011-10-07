#include "mo/rule/RedundantLocalVariableRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Decl.h>
#include <clang/AST/Stmt.h>
#include <clang/AST/Expr.h>

using namespace clang;

RuleSet RedundantLocalVariableRule::rules(new RedundantLocalVariableRule());

void RedundantLocalVariableRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorUtil::getStmt(node);
  Stmt *parentStmt = CursorUtil::getStmt(parentNode);
  if (stmt && parentStmt) {
    ReturnStmt *returnStmt = dyn_cast<ReturnStmt>(stmt);
    CompoundStmt *compoundStmt = dyn_cast<CompoundStmt>(parentStmt);
    if (returnStmt && compoundStmt && compoundStmt->size() >= 2) {
      Stmt *lastSecondStmt = (Stmt *)*(compoundStmt->body_end() - 2);
      DeclStmt *declStmt = dyn_cast<DeclStmt>(lastSecondStmt);
      Expr *returnValue = returnStmt->getRetValue();
      if (returnValue && declStmt && declStmt->isSingleDecl()) {
        NamedDecl *variableDecl = dyn_cast<NamedDecl>(declStmt->getSingleDecl());
        ImplicitCastExpr *implicitCastExpr = dyn_cast<ImplicitCastExpr>(returnValue);
        if (variableDecl && implicitCastExpr) {
          DeclRefExpr *returnExpr = dyn_cast<DeclRefExpr>(implicitCastExpr->getSubExpr());
          if (returnExpr) {
            NamedDecl *namedDecl = returnExpr->getFoundDecl();
            if (namedDecl && variableDecl->getName().equals(namedDecl->getName())) {
              Violation violation(node, this);
              violationSet.addViolation(violation);
            }
          }
        }
      }
    }
  }
}

const string RedundantLocalVariableRule::name() const {
  return "redundant local variable";
}
