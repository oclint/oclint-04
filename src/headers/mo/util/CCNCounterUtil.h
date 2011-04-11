#ifndef MO_UTIL_CCNCOUNTERUTIL_H
#define MO_UTIL_CCNCOUNTERUTIL_H

#include <clang-c/Index.h>

class CCNCounterUtil {
public:
  static int getCCNOfCursor(CXCursor node);
};

enum CXChildVisitResult ccnTraverseAST(CXCursor node, CXCursor parentNode, CXClientData clientData);

#endif
