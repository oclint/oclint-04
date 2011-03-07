#include "mo/util/TestCursorUtil.h"
#include "mo/util/CursorUtil.h"
#include "mo/RuleViolation.h"
#include "mo/RuleData.h"
#include "mo/rule/MockRule.h"

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

CXCursor& TestCursorUtil::getSwitchStmtCursor() {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, "test/samples/SwitchStatement.m", 0, 0, 0, 0, CXTranslationUnit_None);
  RuleData *data = new RuleData();
  clang_visitChildren(clang_getTranslationUnitCursor(translationUnit), extractSwitchStmtCursor, data);
  RuleViolation violation = data->getViolations().at(0);
  CXCursor switchStmtCursor = violation.cursor;
  // As we need to use a Cursor within the TranslationUnit, so we cannot
  // use disposeTranslationUnit method to release memory
  // clang_disposeTranslationUnit(translationUnit);
  // clang_disposeIndex(index);
  return switchStmtCursor;
}
