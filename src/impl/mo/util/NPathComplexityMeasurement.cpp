#include "mo/util/NPathComplexityMeasurement.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/StmtCXX.h>
#include <clang/AST/StmtObjC.h>
#include <clang/AST/Expr.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/ExprObjC.h>

using namespace clang;

#include <iostream>
using namespace std;

int NPathComplexityMeasurement::nPath(Stmt *stmt) {
  cout << "npath Stmt" << endl;
  if (isa<CompoundStmt>(stmt)) {
    return nPath(dyn_cast<CompoundStmt>(stmt));
  }
  if (isa<IfStmt>(stmt)) {
    return nPath(dyn_cast<IfStmt>(stmt));
  }
  return 1;
}

int NPathComplexityMeasurement::nPath(CompoundStmt *stmt) {
  cout << "npath CompoundStmt" << endl;
  int npath = 1;
  for (CompoundStmt::body_iterator body = stmt->body_begin(), bodyEnd = stmt->body_end(); body != bodyEnd; body++) {
    npath *= nPath(*body);
  }
  return npath;
}

int NPathComplexityMeasurement::nPath(IfStmt *stmt) {
  cout << "npath IfStmt" << endl;
  int nPathElseStmt = 1;
  Stmt *elseStmt = stmt->getElse();
  if (elseStmt) {
    nPathElseStmt = nPath(elseStmt);
  }
  return nPath(stmt->getCond()) + nPath(stmt->getThen()) + nPathElseStmt;
}

int NPathComplexityMeasurement::nPath(Expr *expr) {
  cout << "npath Expr" << endl;
  if (isa<BinaryOperator>(expr)) {
    return nPath(dyn_cast<BinaryOperator>(expr));
  }
  return 0;
}

int NPathComplexityMeasurement::nPath(ConditionalOperator *expr) {
  cout << "npath ConditionalOperator" << endl;
  return 0;
}

int NPathComplexityMeasurement::nPath(BinaryOperator *expr) {
  cout << "npath BinaryOperator" << endl;
  if (expr->getOpcode() == BO_LAnd || expr->getOpcode() == BO_LOr) {
    return 1 + nPath(expr->getLHS()) + nPath(expr->getRHS());
  }
  return 0;
}

int NPathComplexityMeasurement::getNPathOfCursor(CXCursor node) {
  CompoundStmt *compoundStmt = NULL;
  Stmt *stmt = CursorUtil::getStmt(node);
  if (stmt && isa<CompoundStmt>(stmt)) {
    compoundStmt = dyn_cast<CompoundStmt>(stmt);
  }
  Decl *decl = CursorUtil::getDecl(node);
  if (decl && (isa<ObjCMethodDecl>(decl) || isa<FunctionDecl>(decl)) && decl->hasBody()) {
    CompoundStmt *bodyStmt = dyn_cast<CompoundStmt>(decl->getBody());
    if (bodyStmt) {
      compoundStmt = bodyStmt;
    }
  }
  if (compoundStmt != NULL) {
    return nPath(compoundStmt);
  }
  return 1; // TODO: return 1 for now, will throw exceptions
}