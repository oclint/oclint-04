#ifndef OCLINT_HELPER_CURSORHELPER_H
#define OCLINT_HELPER_CURSORHELPER_H

#include <string>

#include <clang-c/Index.h>

namespace clang
{
  class Decl;
  class Stmt;
  class Expr;
  class ASTContext;
}

using namespace clang;
using namespace std;

class CursorHelper
{
private:
  static string itoa(int i);

public:
  static Decl* getDecl(CXCursor node);
  static Stmt* getStmt(CXCursor node);
  static Expr* getExpr(CXCursor node);
  static ASTContext& getASTContext(CXCursor node);
  static bool isCursorDeclaredInCurrentFile(CXCursor node);
  static string getFileName(CXCursor cursor);
  static string getLineNumber(CXCursor cursor);
  static string getColumnNumber(CXCursor cursor);
};

#endif
