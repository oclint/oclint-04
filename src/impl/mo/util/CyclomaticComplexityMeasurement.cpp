#include <clang/AST/Stmt.h>
#include <clang/AST/StmtCXX.h>
#include <clang/AST/StmtObjC.h>
#include <clang/AST/Expr.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/ExprObjC.h>

using namespace clang;

#include "mo/util/CursorUtil.h"
#include "mo/util/CyclomaticComplexityMeasurement.h"

static int _count;

int CyclomaticComplexityMeasurement::getCCNOfCursor(CXCursor node) {
  _count = 0;
  clang_visitChildren(node, ccnTraverseAST, 0);
  return _count + 1;
}

bool isDecisionPoint(Stmt *stmt) {
  return isa<IfStmt>(stmt) || isa<ForStmt>(stmt) || isa<ObjCForCollectionStmt>(stmt) || 
    isa<WhileStmt>(stmt) || isa<DoStmt>(stmt) || isa<CaseStmt>(stmt) || isa<ObjCAtCatchStmt>(stmt);
}

bool isDecisionPoint(Expr *expr) {
  if (isa<ConditionalOperator>(expr)) {
    return true;
  }
  
  BinaryOperator *biOperator = dyn_cast<BinaryOperator>(expr);
  if (biOperator && (biOperator->getOpcode() == BO_LAnd || biOperator->getOpcode() == BO_LOr)) {
    return true;
  }
  
  return false;
}

enum CXChildVisitResult ccnTraverseAST(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  Stmt *stmt = CursorUtil::getStmt(node);
  if (stmt && isDecisionPoint(stmt)) {
    _count++;
  }
  Expr *expr = CursorUtil::getExpr(node);
  if (expr && isDecisionPoint(expr)) {
    _count++;
  }
  return CXChildVisit_Recurse;
}
