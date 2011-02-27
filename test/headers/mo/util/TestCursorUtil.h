#ifndef MO_TESTCURSORUTIL_H
#define MO_TESTCURSORUTIL_H

#include <clang-c/Index.h>

class TestCursorUtil {
public:
  static CXCursor getSwitchStmtCursor();
};

#endif
