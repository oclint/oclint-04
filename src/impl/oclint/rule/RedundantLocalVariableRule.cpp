#include "oclint/rule/RedundantLocalVariableRule.h"
#include "oclint/RuleSet.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/helper/CursorHelper.h"

#include <clang/AST/Decl.h>
#include <clang/AST/Stmt.h>
#include <clang/AST/Expr.h>

using namespace clang;

RuleSet RedundantLocalVariableRule::rules(new RedundantLocalVariableRule());

NamedDecl* RedundantLocalVariableRule::extractFromReturnStmt(Stmt *stmt) {
  ReturnStmt *returnStmt = dyn_cast<ReturnStmt>(stmt);
  if (returnStmt) {
    Expr *returnValue = returnStmt->getRetValue();
    if (returnValue) {
      ImplicitCastExpr *implicitCastExpr = dyn_cast<ImplicitCastExpr>(returnValue);
      if (implicitCastExpr) {
        DeclRefExpr *returnExpr = dyn_cast<DeclRefExpr>(implicitCastExpr->getSubExpr());
        if (returnExpr) {
          return returnExpr->getFoundDecl();
        }
      }
    }
  }
  return NULL;
}

NamedDecl* RedundantLocalVariableRule::extractFromDeclStmt(Stmt *stmt) {
  CompoundStmt *compoundStmt = dyn_cast<CompoundStmt>(stmt);
  if (compoundStmt && compoundStmt->size() >= 2) {
    Stmt *lastSecondStmt = (Stmt *)*(compoundStmt->body_end() - 2);
    DeclStmt *declStmt = dyn_cast<DeclStmt>(lastSecondStmt);
    if (declStmt && declStmt->isSingleDecl()) {
      return dyn_cast<NamedDecl>(declStmt->getSingleDecl());
    }
  }
  return NULL;
}

void RedundantLocalVariableRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorHelper::getStmt(node);
  Stmt *parentStmt = CursorHelper::getStmt(parentNode);
  if (stmt && parentStmt) {
    NamedDecl *returnDeclRef = extractFromReturnStmt(stmt);
    NamedDecl *namedDecl = extractFromDeclStmt(parentStmt);
    if (returnDeclRef && namedDecl && returnDeclRef->getName().equals(namedDecl->getName())) {
      Violation violation(node, this);
      violationSet.addViolation(violation);
    }
  }
}

const string RedundantLocalVariableRule::name() const {
  return "redundant local variable";
}
