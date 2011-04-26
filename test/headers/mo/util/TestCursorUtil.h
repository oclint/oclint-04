#ifndef MO_UTIL_TESTCURSORUTIL_H
#define MO_UTIL_TESTCURSORUTIL_H

#include <clang-c/Index.h>

class StringSourceCode;

class TestCursorUtil {
public:
  static const CXCursor getSwitchStmtCursor(StringSourceCode code);
};

#endif
