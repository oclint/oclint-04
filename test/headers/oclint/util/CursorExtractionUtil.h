#ifndef OCLINT_UTIL_CURSOREXTRACTIONUTIL_H
#define OCLINT_UTIL_CURSOREXTRACTIONUTIL_H

#include <clang-c/Index.h>

#include <vector>
#include <utility>
using namespace std;

class StringSourceCode;

const pair<CXCursor, CXCursor> extractCursor(StringSourceCode code, bool(^nodesFilter)(CXCursor, CXCursor), int filteredIndex = 0);

#endif
