#include "mo/util/CursorExtractionUtil.h"
#include "mo/Violation.h"
#include "mo/ViolationSet.h"
#include "mo/rule/MockRule.h"
#include "mo/util/StringSourceCodeToTranslationUnitUtil.h"

enum CXChildVisitResult extractCursorVisitor(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  vector<pair<CXCursor, CXCursor> > *nodes = (vector<pair<CXCursor, CXCursor> > *)clientData;
  nodes->push_back(make_pair(node, parentNode));
  return CXChildVisit_Recurse;
}

const pair<CXCursor, CXCursor> extractCursor(StringSourceCode code, bool(^nodesFilter)(CXCursor, CXCursor), int filteredIndex) {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(code, index);
  vector<pair<CXCursor, CXCursor> > *nodes = new vector<pair<CXCursor, CXCursor> >();
  clang_visitChildren(clang_getTranslationUnitCursor(translationUnit), extractCursorVisitor, nodes);
  
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
