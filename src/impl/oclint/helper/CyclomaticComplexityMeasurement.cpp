#include <clang/AST/Stmt.h>
#include <clang/AST/StmtCXX.h>
#include <clang/AST/StmtObjC.h>
#include <clang/AST/Expr.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/ExprObjC.h>

using namespace clang;

#include "oclint/helper/CursorHelper.h"
#include "oclint/helper/CyclomaticComplexityMeasurement.h"

static int _count;

int CyclomaticComplexityMeasurement::getCCNOfCursor(CXCursor node) {
  _count = 0;
  clang_visitChildrenWithBlock(node, ^(CXCursor cursor, CXCursor parentCursor) {
    Stmt *stmt = CursorHelper::getStmt(cursor);
    if (stmt && isDecisionPoint(stmt)) {
      _count++;
    }
    Expr *expr = CursorHelper::getExpr(cursor);
    if (expr && isDecisionPoint(expr)) {
      _count++;
    }
    return CXChildVisit_Recurse;
  });
  return _count + 1;
}

bool CyclomaticComplexityMeasurement::isDecisionPoint(Stmt *stmt) {
  return isa<IfStmt>(stmt) || isa<ForStmt>(stmt) || isa<ObjCForCollectionStmt>(stmt) || 
    isa<WhileStmt>(stmt) || isa<DoStmt>(stmt) || isa<CaseStmt>(stmt) || isa<ObjCAtCatchStmt>(stmt);
}

bool CyclomaticComplexityMeasurement::isDecisionPoint(Expr *expr) {
  if (isa<ConditionalOperator>(expr)) {
    return true;
  }
  
  BinaryOperator *biOperator = dyn_cast<BinaryOperator>(expr);
  return biOperator && (biOperator->getOpcode() == BO_LAnd || biOperator->getOpcode() == BO_LOr);
}
