#include "mo/util/TestCursorUtil.h"
#include "mo/util/CursorUtil.h"
#include "mo/RuleViolation.h"
#include "mo/RuleData.h"
#include "mo/rule/MockRule.h"
#include "mo/util/StringSourceCodeToTranslationUnitUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

enum CXChildVisitResult extractSwitchStmtCursor(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  RuleData *data = (RuleData *)clientData;
  if (Stmt *stmt = CursorUtil::getStmt(node)) {
    if (isa<SwitchStmt>(stmt)) {
      RuleViolation violation(node, new MockRule());
      data->addViolation(violation);
    }
  }
  return CXChildVisit_Recurse;
}

const CXCursor TestCursorUtil::getSwitchStmtCursor(StringSourceCode code) {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(code, index);
  RuleData *data = new RuleData();
  clang_visitChildren(clang_getTranslationUnitCursor(translationUnit), extractSwitchStmtCursor, data);
  RuleViolation violation = data->getViolations().at(0);
  return violation.cursor;
}
