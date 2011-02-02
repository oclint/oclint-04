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

#include "mo/rule/AbstractRule.h"
#include "mo/rule/Violation.h"

class ASTVisitor : public RecursiveASTVisitor<ASTVisitor> {
private:
  Violation *_violation;
  vector<AbstractRule*> _rules;
  
public:
  ASTVisitor(vector<AbstractRule*> &rules, Violation *violation) {
    _rules = rules;
    _violation = violation;
  }
  
  bool traverse(Decl *decl);
  bool traverse(Stmt *stmt);
  bool TraverseDecl(Decl *decl);
  bool TraverseStmt(Stmt *stmt);
};

#endif
