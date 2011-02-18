#include "mo/TraverseAST.h"
#include "mo/RuleViolation.h"
#include "mo/RuleData.h"
#include "mo/Rule.h"

enum CXChildVisitResult traverseAST(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  RuleData *data = (RuleData *)clientData;
  Rule *rule = data->getRule();
  RuleViolation *violation = data->getViolation();
  rule->apply(node, parentNode, *violation);
  return CXChildVisit_Recurse;
}
