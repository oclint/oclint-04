#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Stmt.h>

#include "oclint/util/CursorUtilTest.h"
#include "oclint/StringSourceCode.h"
#include "oclint/util/CursorExtractionUtil.h"
#include "oclint/util/StringSourceCodeToTranslationUnitUtil.h"

CXCursor getNullCursor() {
  return clang_getNullCursor();
}

CXCursor getDeclCursor() {
  CXCursor cursor = { CXCursor_FirstDecl, { (void*)1, 0, 0 } };
  return cursor;
}

CXCursor getStmtCursor() {
  CXCursor cursor = { CXCursor_FirstStmt, { 0, (void*)1, 0 } };
  return cursor;
}

CXCursor getExprCursor() {
  CXCursor cursor = { CXCursor_FirstExpr, { 0, (void*)1, 0 } };
  return cursor;
}

void CursorUtilTest::testGetDeclWithDeclCursor() {
  CXCursor cursor = getDeclCursor();
  Decl *decl = CursorUtil::getDecl(cursor);
  TS_ASSERT(decl);
}

void CursorUtilTest::testGetDeclWithNotDeclCursor() {
  CXCursor cursor = getStmtCursor();
  Decl *decl = CursorUtil::getDecl(cursor);
  TS_ASSERT(!decl);
}

void CursorUtilTest::testGetDeclWithNullCursor() {
  CXCursor cursor = getNullCursor();
  Decl *decl = CursorUtil::getDecl(cursor);
  TS_ASSERT(!decl);
}

void CursorUtilTest::testGetStmtWithStmtCursor() {
  CXCursor cursor = getStmtCursor();
  Stmt *stmt = CursorUtil::getStmt(cursor);
  TS_ASSERT(stmt);
}

void CursorUtilTest::testGetStmtWithNotStmtCursor() {
  CXCursor cursor = getDeclCursor();
  Stmt *stmt = CursorUtil::getStmt(cursor);
  TS_ASSERT(!stmt);
}

void CursorUtilTest::testGetStmtWithNullCursor() {
  CXCursor cursor = getNullCursor();
  Stmt *stmt = CursorUtil::getStmt(cursor);
  TS_ASSERT(!stmt);
}

void CursorUtilTest::testGetExprWithExprCursor() {
  CXCursor cursor = getExprCursor();
  Expr *expr = CursorUtil::getExpr(cursor);
  TS_ASSERT(expr);
}

void CursorUtilTest::testGetExprWithNotExprCursor() {
  CXCursor cursor = getDeclCursor();
  Expr *expr = CursorUtil::getExpr(cursor);
  TS_ASSERT(!expr);
}

void CursorUtilTest::testGetExprWithNullCursor() {
  CXCursor cursor = getNullCursor();
  Expr *expr = CursorUtil::getExpr(cursor);
  TS_ASSERT(!expr);
}

void CursorUtilTest::testGetExprWithStmtCursor() {
  CXCursor cursor = getStmtCursor();
  Expr *expr = CursorUtil::getExpr(cursor);
  TS_ASSERT(!expr);
}

void CursorUtilTest::testGetCursorASTContext() {
  StringSourceCode strCode("int main() { return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    return true;
  });
  TS_ASSERT_EQUALS(CursorUtil::getASTContext(cursorPair.first).getTranslationUnitDecl(), CursorUtil::getASTContext(cursorPair.second).getTranslationUnitDecl());
}

void CursorUtilTest::testIsCursorDeclaredInCurrentFile() {
  StringSourceCode strCode("#import <Foundation/Foundation.h>\nint main() { return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<FunctionDecl>(decl);
  });
  TS_ASSERT(!CursorUtil::isCursorDeclaredInCurrentFile(cursorPair.first));
}

void CursorUtilTest::testIsCursorDeclaredInHeaderFiles() {
  StringSourceCode strCode("#import <Foundation/Foundation.h>\nint main() { return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Decl *decl = CursorUtil::getDecl(node);
    return decl && isa<FunctionDecl>(decl);
  }, -1);
  TS_ASSERT(CursorUtil::isCursorDeclaredInCurrentFile(cursorPair.first));
}

void CursorUtilTest::testGetFileName() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorUtil::getStmt(node);
    return stmt && isa<SwitchStmt>(stmt);
  });
  int tmpFileNameLength = StringSourceCodeToTranslationUnitUtil::lengthOfTmpFileName(strCode);
  TS_ASSERT_EQUALS(CursorUtil::getFileName(cursorPair.first).length(), tmpFileNameLength);
}

void CursorUtilTest::testGetLineNumber() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorUtil::getStmt(node);
    return stmt && isa<SwitchStmt>(stmt);
  });
  TS_ASSERT_EQUALS(CursorUtil::getLineNumber(cursorPair.first), "1");
}

void CursorUtilTest::testGetColumnNumber() {
  StringSourceCode strCode("int main() { int i = 1; switch (i) { case 1: break; } return 0; }", "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorUtil::getStmt(node);
    return stmt && isa<SwitchStmt>(stmt);
  });
  TS_ASSERT_EQUALS(CursorUtil::getColumnNumber(cursorPair.first), "25");
}