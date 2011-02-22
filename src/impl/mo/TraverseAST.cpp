#include "mo/TraverseAST.h"
#include "mo/RuleViolation.h"
#include "mo/RuleData.h"
#include "mo/Rule.h"

enum CXChildVisitResult traverseAST(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  RuleData *data = (RuleData *)clientData;
  for (int index = 0, numberOfRules = data->numberOfRules(); index != numberOfRules; index++) {
    data->ruleAt(index)->apply(node, parentNode, *data);
  }
  return CXChildVisit_Recurse;
}
