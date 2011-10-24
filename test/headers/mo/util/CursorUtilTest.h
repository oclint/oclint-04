#include <cxxtest/TestSuite.h>
#include "mo/util/CursorUtil.h"

class CursorUtilTest : public CxxTest::TestSuite { 
public:
  void testGetDeclWithDeclCursor();
  void testGetDeclWithNotDeclCursor();
  void testGetDeclWithNullCursor();
  void testGetStmtWithStmtCursor();
  void testGetStmtWithNotStmtCursor();
  void testGetStmtWithNullCursor();
  void testGetExprWithExprCursor();
  void testGetExprWithNotExprCursor();
  void testGetExprWithNullCursor();
  void testGetExprWithStmtCursor();
  void testGetCursorASTContext();
  void testIsCursorDeclaredInCurrentFile();
  void testIsCursorDeclaredInHeaderFiles();
};
