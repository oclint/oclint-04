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
};
