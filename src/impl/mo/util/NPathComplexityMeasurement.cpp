#include "mo/util/NPathComplexityMeasurement.h"
#include "mo/util/CursorUtil.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/StmtCXX.h>
#include <clang/AST/StmtObjC.h>
#include <clang/AST/Expr.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/ExprObjC.h>

using namespace clang;

#define DISPATH(STMT_TYPE) if (isa<STMT_TYPE>(node)) return nPath(dyn_cast<STMT_TYPE>(node))

int NPathComplexityMeasurement::nPath(Stmt *node) {
  if (node) {
    DISPATH(CompoundStmt);
    DISPATH(IfStmt);
    DISPATH(WhileStmt);
    DISPATH(DoStmt);
    DISPATH(ForStmt);
    DISPATH(SwitchStmt);
    DISPATH(ObjCForCollectionStmt);
  }
  return 1;
}

int NPathComplexityMeasurement::nPath(CompoundStmt *stmt) {
  int npath = 1;
  for (CompoundStmt::body_iterator body = stmt->body_begin(), bodyEnd = stmt->body_end(); 
      body != bodyEnd; body++) {
    npath *= nPath(*body);
  }
  return npath;
}

int NPathComplexityMeasurement::nPath(IfStmt *stmt) {
  int nPathElseStmt = 1;
  Stmt *elseStmt = stmt->getElse();
  if (elseStmt) {
    nPathElseStmt = nPath(elseStmt);
  }
  return nPath(stmt->getCond()) + nPath(stmt->getThen()) + nPathElseStmt;
}

int NPathComplexityMeasurement::nPath(WhileStmt *stmt) {
  return nPath(stmt->getCond()) + nPath(stmt->getBody()) + 1;
}

int NPathComplexityMeasurement::nPath(DoStmt *stmt) {
  return nPath(stmt->getCond()) + nPath(stmt->getBody()) + 1;
}

int NPathComplexityMeasurement::nPath(ForStmt *stmt) {
  // TODO: 
  // Base on Nejmeh's NPATH, the first expression is used to initialize a loop control variable,
  // But the first child node for For statment is a statement in Clang's AST.
  // So here we need to be clear that if it's a statement or an expression
  // If it's a statement, meaning, a sequential statement, npath will be 1
  // If it's an expression, on the contrary, without && or ||, npath should be 0
  // For the implementation below, we treat it as a statement for now.
  
  // And I realize here that, as a note:
  // If statment and If-Else statement are most easy cases to understand the nPath concept.
  // And both switch statement and for statement can be converted to if statement,
  // however, I noticed that, with the same logic, if the presentation formats are different,
  // the NPath of it may vary, 
  // for example, for the following if statement
  // if (i == 1) { foo(1); } if (i == 2) { foo(2); }
  // NPath of it will be 4
  // However, if convert to switch statement, it will be
  // switch (i) { case 1: foo(1); break; case 2: foo(2); break; }, the NPath is 2 here
  // Converted to for statement, it is
  // for (int i = 1; i <= 2; i++) { foo(i); }, the NPath is 3
  // As a conclusion, in my opinion, same logic in different formats should not reduce the complexity
  // However, here, I will follow Nejmeh's NPath
  
  return nPath(stmt->getInit()) + nPath(stmt->getCond()) + nPath(stmt->getInc()) 
          + nPath(stmt->getBody()) + 1;
}

int NPathComplexityMeasurement::nPath(ObjCForCollectionStmt *stmt) {
  // If we convert a foreach loop to a simple for loop, it will looks like
  // for (int i = 0; i < [anArray count]; i++) {
  //   id it = [anArray objectAtIndex:i];
  //   ... (same as foreach loop block)
  // }
  // So, convert to same logic in for statement, we assume the NPath complexity as below
  // NP(Foreach) :=￼NP((for-range)) + 2
  
  return nPath(stmt->getBody()) + 2;
}

int NPathComplexityMeasurement::nPath(SwitchStmt *stmt) {
  int internalNPath = 0, nPathSwitchStmt = nPath(stmt->getCond());
  CompoundStmt *body = (CompoundStmt *)stmt->getBody();
  for (CompoundStmt::body_iterator bodyStmt = body->body_begin(), bodyStmtEnd = body->body_end(); 
        bodyStmt != bodyStmtEnd; bodyStmt++) {
    if (isa<SwitchCase>(*bodyStmt)) {
      SwitchCase *switchCase = dyn_cast<SwitchCase>(*bodyStmt);
      nPathSwitchStmt += internalNPath;
      internalNPath = nPath(switchCase->getSubStmt());
    }
    else {
      internalNPath *= nPath(*bodyStmt);
    }
  }
  return nPathSwitchStmt + internalNPath;
}

int NPathComplexityMeasurement::nPath(Expr *node) {
  if (node) {
    DISPATH(ConditionalOperator);
    DISPATH(BinaryOperator);
    DISPATH(ParenExpr);
  }
  return 0;
}

int NPathComplexityMeasurement::nPath(ConditionalOperator *expr) {
  return nPath(expr->getCond()) + nPath(expr->getTrueExpr()) + nPath(expr->getFalseExpr()) + 2;
}

int NPathComplexityMeasurement::nPath(BinaryOperator *expr) {
  if (expr->getOpcode() == BO_LAnd || expr->getOpcode() == BO_LOr) {
    return 1 + nPath(expr->getLHS()) + nPath(expr->getRHS());
  }
  return 0;
}

int NPathComplexityMeasurement::nPath(ParenExpr *expr) {
  return nPath(expr->getSubExpr());
}

int NPathComplexityMeasurement::getNPathOfCursor(CXCursor cursor) {
  CompoundStmt *compoundStmt = extractCompoundStmtFromCursor(cursor);
  if (compoundStmt == NULL) {
    compoundStmt = extractCompoundStmtFromMethodDeclCursor(cursor);
  }
  if (compoundStmt != NULL) {
    return nPath(compoundStmt);
  }
  return 1; // TODO: return 1 for now, will throw exceptions
}

CompoundStmt* NPathComplexityMeasurement::extractCompoundStmtFromCursor(CXCursor cursor) {
  Stmt *stmt = CursorUtil::getStmt(cursor);
  if (stmt && isa<CompoundStmt>(stmt)) {
    return dyn_cast<CompoundStmt>(stmt);
  }
  return NULL;
}

CompoundStmt* NPathComplexityMeasurement::extractCompoundStmtFromMethodDeclCursor(CXCursor cursor) {
  Decl *decl = CursorUtil::getDecl(cursor);
  if (decl && (isa<ObjCMethodDecl>(decl) || isa<FunctionDecl>(decl)) && decl->hasBody()) {
    CompoundStmt *bodyStmt = dyn_cast<CompoundStmt>(decl->getBody());
    if (bodyStmt) {
      return bodyStmt;
    }
  }
  return NULL;
}
