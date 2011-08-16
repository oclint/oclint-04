#include "mo/TraverseAST.h"
#include "mo/RuleViolation.h"
#include "mo/ViolationSet.h"
#include "mo/Rule.h"
#include "mo/ruleset/RuleSet.h"

enum CXChildVisitResult traverseAST(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  ViolationSet *violationSet = (ViolationSet *)clientData;
  RuleSet::apply(node, parentNode, *violationSet);
  return CXChildVisit_Recurse;
}
