#include "mo/TraverseAST.h"
#include "mo/RuleViolation.h"

enum CXChildVisitResult traverseAST(CXCursor node, CXCursor parentNode, CXClientData violations) {
  // RuleViolation *violation = (RuleViolation *)violations;
  return CXChildVisit_Recurse;
}
