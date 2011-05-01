#include "mo/TraverseAST.h"
#include "mo/RuleViolation.h"
#include "mo/RuleData.h"
#include "mo/Rule.h"
#include "mo/ruleset/RuleSet.h"

enum CXChildVisitResult traverseAST(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  RuleData *data = (RuleData *)clientData;
  RuleSet::apply(node, parentNode, *data);
  return CXChildVisit_Recurse;
}
