#include "oclint/rule/RedundantIfStatementRule.h"
#include "oclint/RuleSet.h"
#include "oclint/ViolationSet.h"
#include "oclint/Violation.h"
#include "oclint/util/CursorUtil.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/Expr.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/ExprObjC.h>

using namespace clang;

RuleSet RedundantIfStatementRule::rules(new RedundantIfStatementRule());

template<typename nodeType>
nodeType* RedundantIfStatementRule::extractStmt(Stmt *fromStmt) {
  if (fromStmt) {
    if (isa<nodeType>(fromStmt)) {
      return dyn_cast<nodeType>(fromStmt);
    }
    CompoundStmt *compoundStmt = dyn_cast<CompoundStmt>(fromStmt);
    if (compoundStmt && compoundStmt->size() == 1) {
      return extractStmt<nodeType>(*(compoundStmt->body_begin()));
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

bool RedundantIfStatementRule::isNotEquals(Expr *firstExpr, Expr *secondExpr) {
  return (isCIntegerViolated(firstExpr, secondExpr) || isCXXBoolViolated(firstExpr, secondExpr) ||
    isObjCBOOLViolated(firstExpr, secondExpr));
}

bool RedundantIfStatementRule::doesReturnStatementsViolateRule(ReturnStmt *first, ReturnStmt *second) {
  return first && second && isNotEquals(first->getRetValue(), second->getRetValue());
}

bool RedundantIfStatementRule::doesBinaryOperatorsViolateRule(BinaryOperator *first, BinaryOperator *second) {
  return first && second && isNotEquals(first->getRHS(), second->getRHS());
}

void RedundantIfStatementRule::apply(CXCursor& node, CXCursor& parentNode, ViolationSet& violationSet) {
  Stmt *stmt = CursorUtil::getStmt(node);
  if (stmt) {
    IfStmt *ifStmt = dyn_cast<IfStmt>(stmt);
    if (ifStmt) {
      ReturnStmt *thenReturnStmt = extractStmt<ReturnStmt>(ifStmt->getThen());
      ReturnStmt *elseReturnStmt = extractStmt<ReturnStmt>(ifStmt->getElse());
      BinaryOperator *thenBinaryOperator = extractStmt<BinaryOperator>(ifStmt->getThen());
      BinaryOperator *elseBinaryOperator = extractStmt<BinaryOperator>(ifStmt->getElse());
      if (doesReturnStatementsViolateRule(thenReturnStmt, elseReturnStmt) || 
          doesBinaryOperatorsViolateRule(thenBinaryOperator, elseBinaryOperator)) {
        Violation violation(node, this);
        violationSet.addViolation(violation);
      }
    }
  }
}

const string RedundantIfStatementRule::name() const {
  return "redundant if statement";
}
