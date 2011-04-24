#include <clang/AST/Stmt.h>
#include <clang/AST/StmtCXX.h>
#include <clang/AST/StmtObjC.h>
#include <clang/AST/Expr.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/ExprObjC.h>

using namespace clang;

#include "mo/util/CursorUtil.h"
#include "mo/util/CCNCounterUtil.h"

static int _count;

int CCNCounterUtil::getCCNOfCursor(CXCursor node) {
  _count = 0;
  clang_visitChildren(node, ccnTraverseAST, 0);
  return _count + 1;
}

enum CXChildVisitResult ccnTraverseAST(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  if (Stmt *stmt = CursorUtil::getStmt(node)) {
    if (isa<IfStmt>(stmt) || isa<ForStmt>(stmt) || isa<ObjCForCollectionStmt>(stmt) || isa<WhileStmt>(stmt) || 
        isa<DoStmt>(stmt) || isa<CaseStmt>(stmt) || isa<ObjCAtCatchStmt>(stmt)) {
      _count++;
    }
  }
  if (Expr *expr = CursorUtil::getExpr(node)) {
    if (isa<ConditionalOperator>(expr)) {
      _count++;
    }
    if (BinaryOperator *biOperator = dyn_cast<BinaryOperator>(expr)) {
      if (biOperator->getOpcode() == BO_LAnd || biOperator->getOpcode() == BO_LOr) {
        _count++;
      }
    }
  }
  return CXChildVisit_Recurse;
}
