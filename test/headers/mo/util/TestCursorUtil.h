#ifndef MO_UTIL_TESTCURSORUTIL_H
#define MO_UTIL_TESTCURSORUTIL_H

#include <clang-c/Index.h>

class StringSourceCode;

class TestCursorUtil {
public:
  static const CXCursor getSwitchStmtCursor(StringSourceCode code);
  static const CXCursor getIfStmtCursor(StringSourceCode code);
  static const CXCursor getVarDeclCursor(StringSourceCode code);
  static const CXCursor getObjCMethodDecl(StringSourceCode code);
  static const CXCursor getFunctionDecl(StringSourceCode code);
};

#endif
