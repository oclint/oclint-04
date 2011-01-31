#ifndef MO_RULE_ABSTRACTRULE_H
#define MO_RULE_ABSTRACTRULE_H

#include <string>

using namespace std;

#include <clang/AST/AST.h>

#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/Stmt.h>
#include <clang/AST/StmtCXX.h>
#include <clang/AST/StmtObjC.h>
#include <clang/AST/Expr.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/ExprObjC.h>

class AbstractRule {
public:
  virtual ~AbstractRule() {}
  
  virtual void applyStmt(Stmt *stmt) {}
  virtual void applyDecl(Decl *decl) {}

  virtual string name() = 0;
  virtual int priority() = 0;

};

#endif
