#include "mo/rule/RedundantIfStatementRule.h"
#include "mo/RuleSet.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/Expr.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/ExprObjC.h>

using namespace clang;

RuleSet RedundantIfStatementRule::rules(new RedundantIfStatementRule());

ReturnStmt* RedundantIfStatementRule::extractReturnStmt(Stmt *fromStmt) {
  if (fromStmt) {
    if (isa<ReturnStmt>(fromStmt)) {
      return dyn_cast<ReturnStmt>(fromStmt);
    }
    CompoundStmt *compoundStmt = dyn_cast<CompoundStmt>(fromStmt);
    if (compoundStmt && compoundStmt->size() == 1) {
      return extractReturnStmt(*(compoundStmt->body_begin()));
    }
  }
  return NULL;
}

bool RedundantIfStatementRule::isCIntegerViolated(Expr *thenExpr, Expr *elseExpr) {
  if (thenExpr && elseExpr) {
    IntegerLiteral *thenInteger = dyn_cast<IntegerLiteral>(thenExpr);
    IntegerLiteral *elseInteger = dyn_cast<IntegerLiteral>(elseExpr);
    return thenInteger && elseInteger && thenInteger->getValue().getBoolValue() != elseInteger->getValue().getBoolValue();
  }
  return false;
}

bool RedundantIfStatementRule::isCXXBoolViolated(Expr *thenExpr, Expr *elseExpr) {
  if (thenExpr && elseExpr) {
    CXXBoolLiteralExpr *thenCXXBool = dyn_cast<CXXBoolLiteralExpr>(thenExpr);
    CXXBoolLiteralExpr *elseCXXBool = dyn_cast<CXXBoolLiteralExpr>(elseExpr);
    return thenCXXBool && elseCXXBool && thenCXXBool->getValue() != elseCXXBool->getValue();
  }
  return false;
}

bool RedundantIfStatementRule::isObjCBOOLViolated(Expr *thenExpr, Expr *elseExpr) {
  if (thenExpr && elseExpr) {
    CStyleCastExpr *thenObjCBOOL = dyn_cast<CStyleCastExpr>(thenExpr);
    CStyleCastExpr *elseObjCBOOL = dyn_cast<CStyleCastExpr>(elseExpr);
    return thenObjCBOOL && elseObjCBOOL && 
      isCIntegerViolated(dyn_cast<IntegerLiteral>(thenObjCBOOL->getSubExpr()), dyn_cast<IntegerLiteral>(elseObjCBOOL->getSubExpr()));
  }
  return false;
}

void RedundantIfStatementRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorUtil::getStmt(node);
  if (stmt) {
    IfStmt *ifStmt = dyn_cast<IfStmt>(stmt);
    if (ifStmt) {
      ReturnStmt *thenStmt = extractReturnStmt(ifStmt->getThen());
      ReturnStmt *elseStmt = extractReturnStmt(ifStmt->getElse());
      if (thenStmt && elseStmt) {
        Expr *thenExpr = thenStmt->getRetValue();
        Expr *elseExpr = elseStmt->getRetValue();
        if (isCIntegerViolated(thenExpr, elseExpr) || isCXXBoolViolated(thenExpr, elseExpr) ||
            isObjCBOOLViolated(thenExpr, elseExpr)) {
          Violation violation(node, this);
          violationSet.addViolation(violation);    
        }
      }
    }
  }
}

const string RedundantIfStatementRule::name() const {
  return "redundant if statement";
}
