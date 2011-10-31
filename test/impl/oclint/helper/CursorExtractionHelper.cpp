#include "oclint/helper/CursorExtractionHelper.h"
#include "oclint/Violation.h"
#include "oclint/ViolationSet.h"
#include "oclint/rule/MockRule.h"
#include "oclint/helper/StringSourceCodeToTranslationUnitHelper.h"

const pair<CXCursor, CXCursor> extractCursor(StringSourceCode code, bool(^nodesFilter)(CXCursor, CXCursor), int filteredIndex) {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = StringSourceCodeToTranslationUnitHelper::compileStringSourceCodeToTranslationUnit(code, index);
  vector<pair<CXCursor, CXCursor> > *nodes = new vector<pair<CXCursor, CXCursor> >();
  clang_visitChildrenWithBlock(clang_getTranslationUnitCursor(translationUnit), ^(CXCursor node, CXCursor parentNode) {
    nodes->push_back(make_pair(node, parentNode));
    return CXChildVisit_Recurse;
  });
  
  vector<pair<CXCursor, CXCursor> > *filteredNodes = new vector<pair<CXCursor, CXCursor> >();
  for (int index = 0; index < nodes->size(); index++) {
    pair<CXCursor, CXCursor> nodesPair = nodes->at(index);
    if (nodesFilter(nodesPair.first, nodesPair.second)) {
      filteredNodes->push_back(nodesPair);
    }
  }
  
  if (filteredIndex < 0) {
    filteredIndex += filteredNodes->size();
  }
  return filteredNodes->at(filteredIndex);
}
