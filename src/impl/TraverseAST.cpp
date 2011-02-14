#include "mo/TraverseAST.h"

enum CXChildVisitResult traverseAST(CXCursor node, CXCursor parentNode, CXClientData violations) {
  return CXChildVisit_Recurse;
}
