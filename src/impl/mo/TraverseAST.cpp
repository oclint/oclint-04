#include "mo/TraverseAST.h"
#include "mo/ViolationSet.h"
#include "mo/RuleSet.h"

enum CXChildVisitResult traverseAST(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  ViolationSet *violationSet = (ViolationSet *)clientData;
  RuleSet::apply(node, parentNode, *violationSet);
  return CXChildVisit_Recurse;
}
