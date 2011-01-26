#include "mo/rule/ASTVisitor.h"

bool ASTVisitor::traverse(Decl *decl) {
  return TraverseDecl(decl);
}

bool ASTVisitor::traverse(Stmt *stmt) {
  return TraverseStmt(stmt);
}

bool ASTVisitor::TraverseDecl(Decl *decl) {
  return RecursiveASTVisitor<ASTVisitor>::TraverseDecl(decl);
}

bool ASTVisitor::TraverseStmt(Stmt *stmt) {
  return RecursiveASTVisitor<ASTVisitor>::TraverseStmt(stmt);
}
