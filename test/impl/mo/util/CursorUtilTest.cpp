#include "mo/util/CursorUtilTest.h"

CXCursor getNullCursor() {
  return clang_getNullCursor();
}

CXCursor getDeclCursor() {
  CXCursor cursor = getNullCursor();
  cursor.kind = CXCursor_FirstDecl;
  int testData = 99;
  cursor.data[0] = &testData;
  return cursor;
}

CXCursor getStmtCursor() {
  CXCursor cursor = getNullCursor();
  cursor.kind = CXCursor_FirstStmt;
  int testData = 98;
  cursor.data[1] = &testData;
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
