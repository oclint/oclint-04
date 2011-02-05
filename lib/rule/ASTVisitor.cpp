#include "mo/rule/ASTVisitor.h"

bool ASTVisitor::traverse(Decl *decl) {
  return TraverseDecl(decl);
}

bool ASTVisitor::traverse(Stmt *stmt) {
  return TraverseStmt(stmt);
}

bool ASTVisitor::TraverseDecl(Decl *decl) {
  if (decl) {
    for (unsigned i = 0, e = _rules.size(); i != e; i++) {
      AbstractRule *rule = _rules[i];
      rule->applyDecl(decl, _violation);
    }
  }
  
  return RecursiveASTVisitor<ASTVisitor>::TraverseDecl(decl);
}

bool ASTVisitor::TraverseStmt(Stmt *stmt) {
  if (stmt) {
    for (unsigned i = 0, e = _rules.size(); i != e; i++) {
      AbstractRule *rule = _rules[i];
      rule->applyStmt(stmt, _violation);
    }
  }
  
  return RecursiveASTVisitor<ASTVisitor>::TraverseStmt(stmt);
}
