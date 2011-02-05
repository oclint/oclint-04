#ifndef MO_RULE_ASTVISITOR_H
#define MO_RULE_ASTVISITOR_H

#include <clang/AST/RecursiveASTVisitor.h>

#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/Stmt.h>
#include <clang/AST/StmtCXX.h>
#include <clang/AST/StmtObjC.h>
#include <clang/AST/Expr.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/ExprObjC.h>

using namespace clang;

class ASTVisitor : public RecursiveASTVisitor<ASTVisitor> {
public:
  bool traverse(Decl *decl);
  bool traverse(Stmt *stmt);
  bool TraverseDecl(Decl *decl);
  bool TraverseStmt(Stmt *stmt);
};

#endif
