#ifndef OCLINT_HELPER_CURSOREXTRACTIONHELPER_H
#define OCLINT_HELPER_CURSOREXTRACTIONHELPER_H

#include <clang-c/Index.h>

#include <vector>
#include <utility>
using namespace std;

class StringSourceCode;

const pair<CXCursor, CXCursor> extractCursor(StringSourceCode code, bool(^nodesFilter)(CXCursor, CXCursor), int filteredIndex = 0);

#endif
