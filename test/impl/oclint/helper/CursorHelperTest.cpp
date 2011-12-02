#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Stmt.h>

#include "oclint/helper/CursorHelperTest.h"
#include "oclint/StringSourceCode.h"
#include "oclint/helper/CursorExtractionHelper.h"
#include "oclint/helper/StringSourceCodeToTranslationUnitHelper.h"

CXCursor getNullCursor() {
  return clang_getNullCursor();
}

CXCursor getDeclCursor() {
  CXCursor cursor = { CXCursor_FirstDecl, 0, { (void*)1, 0, 0 } };
  return cursor;
}

CXCursor getStmtCursor() {
  CXCursor cursor = { CXCursor_FirstStmt, 0, { 0, (void*)1, 0 } };
  return cursor;
}

CXCursor getExprCursor() {
  CXCursor cursor = { CXCursor_FirstExpr, 0, { 0, (void*)1, 0 } };
  return cursor;
}

void CursorHelperTest::testGetDeclWithDeclCursor() {
  CXCursor cursor = getDeclCursor();
  Decl *decl = CursorHelper::getDecl(cursor);
  TS_ASSERT(decl);
}

void CursorHelperTest::testGetDeclWithNotDeclCursor() {
  CXCursor cursor = getStmtCursor();
  Decl *decl = CursorHelper::getDecl(cursor);
  TS_ASSERT(!decl);
}

void CursorHelperTest::testGetDeclWithNullCursor() {
  CXCursor cursor = getNullCursor();
  Decl *decl = CursorHelper::getDecl(cursor);
  TS_ASSERT(!decl);
}

void CursorHelperTest::testGetStmtWithStmtCursor() {
  CXCursor cursor = getStmtCursor();
  Stmt *stmt = CursorHelper::getStmt(cursor);
  TS_ASSERT(stmt);
}

void CursorHelperTest::testGetStmtWithNotStmtCursor() {
  CXCursor cursor = getDeclCursor();
  Stmt *stmt = CursorHelper::getStmt(cursor);
  TS_ASSERT(!stmt);
}

void CursorHelperTest::testGetStmtWithNullCursor() {
  CXCursor cursor = getNullCursor();
  Stmt *stmt = CursorHelper::getStmt(cursor);
  TS_ASSERT(!stmt);
}

void CursorHelperTest::testGetExprWithExprCursor() {
  CXCursor cursor = getExprCursor();
  Expr *expr = CursorHelper::getExpr(cursor);
  TS_ASSERT(expr);
}

void CursorHelperTest::testGetExprWithNotExprCursor() {
  CXCursor cursor = getDeclCursor();
  Expr *expr = CursorHelper::getExpr(cursor);
  TS_ASSERT(!expr);
}

void CursorHelperTest::testGetExprWithNullCursor() {
  CXCursor cursor = getNullCursor();
  Expr *expr = CursorHelper::getExpr(cursor);
  TS_ASSERT(!expr);
}

void CursorHelperTest::testGetExprWithStmtCursor() {
  CXCursor cursor = getStmtCursor();
  Expr *expr = CursorHelper::getExpr(cursor);
  TS_ASSERT(!expr);
}

void CursorHelperTest::testGetCursorASTContext() {
  StringSourceCode strCode("int main() { return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    return true;
  });
  TS_ASSERT_EQUALS(CursorHelper::getASTContext(cursorPair.first).getTranslationUnitDecl(), CursorHelper::getASTContext(cursorPair.second).getTranslationUnitDecl());
}

void CursorHelperTest::testIsCursorDeclaredInCurrentFile() {
  StringSourceCode strCode("#import <Foundation/Foundation.h>\nint main() { return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<FunctionDecl>(decl);
  });
  TS_ASSERT(!CursorHelper::isCursorDeclaredInCurrentFile(cursorPair.first));
}

void CursorHelperTest::testIsCursorDeclaredInHeaderFiles() {
  StringSourceCode strCode("#import <Foundation/Foundation.h>\nint main() { return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorHelper::getDecl(node);
    return decl && isa<FunctionDecl>(decl);
  }, -1);
  TS_ASSERT(CursorHelper::isCursorDeclaredInCurrentFile(cursorPair.first));
}

void CursorHelperTest::testGetFileName() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorHelper::getStmt(node);
    return stmt && isa<SwitchStmt>(stmt);
  });
  int tmpFileNameLength = StringSourceCodeToTranslationUnitHelper::lengthOfTmpFileName(strCode);
  TS_ASSERT_EQUALS(CursorHelper::getFileName(cursorPair.first).length(), tmpFileNameLength);
}

void CursorHelperTest::testGetLineNumber() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorHelper::getStmt(node);
    return stmt && isa<SwitchStmt>(stmt);
  });
  TS_ASSERT_EQUALS(CursorHelper::getLineNumber(cursorPair.first), "1");
}

void CursorHelperTest::testGetColumnNumber() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorHelper::getStmt(node);
    return stmt && isa<SwitchStmt>(stmt);
  });
  TS_ASSERT_EQUALS(CursorHelper::getColumnNumber(cursorPair.first), "25");
}