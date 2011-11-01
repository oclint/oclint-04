#include <cxxtest/TestSuite.h>
#include "oclint/helper/CursorHelper.h"

class CursorHelperTest : public CxxTest::TestSuite { 
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
  void testGetFileName();
  void testGetLineNumber();
  void testGetColumnNumber();
};
