#include "mo/util/TestCursorUtil.h"
#include "mo/util/CursorUtil.h"
#include "mo/Violation.h"
#include "mo/ViolationSet.h"
#include "mo/rule/MockRule.h"
#include "mo/util/StringSourceCodeToTranslationUnitUtil.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/Decl.h>
#include <clang/AST/DeclObjC.h>
#include <clang/AST/Expr.h>

using namespace clang;

enum CXChildVisitResult extractSwitchStmtCursor(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  ViolationSet *violationSet = (ViolationSet *)clientData;
  if (Stmt *stmt = CursorUtil::getStmt(node)) {
    if (isa<SwitchStmt>(stmt)) {
      Violation violation(node, new MockRule());
      violationSet->addViolation(violation);
    }
  }
  return CXChildVisit_Recurse;
}

const CXCursor TestCursorUtil::getSwitchStmtCursor(StringSourceCode code) {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(code, index);
  ViolationSet *violationSet = new ViolationSet();
  clang_visitChildren(clang_getTranslationUnitCursor(translationUnit), extractSwitchStmtCursor, violationSet);
  Violation violation = violationSet->getViolations().at(0);
  return violation.cursor;
}

enum CXChildVisitResult extractIfStmtCursor(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  ViolationSet *violationSet = (ViolationSet *)clientData;
  if (Stmt *stmt = CursorUtil::getStmt(node)) {
    if (isa<IfStmt>(stmt)) {
      Violation violation(node, new MockRule());
      violationSet->addViolation(violation);
    }
  }
  return CXChildVisit_Recurse;
}

const CXCursor TestCursorUtil::getIfStmtCursor(StringSourceCode code) {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(code, index);
  ViolationSet *violationSet = new ViolationSet();
  clang_visitChildren(clang_getTranslationUnitCursor(translationUnit), extractIfStmtCursor, violationSet);
  Violation violation = violationSet->getViolations().at(0);
  return violation.cursor;
}

enum CXChildVisitResult extractParmVarDeclCursor(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  ViolationSet *violationSet = (ViolationSet *)clientData;
  if (Decl *decl = CursorUtil::getDecl(node)) {
    if (isa<ParmVarDecl>(decl)) {
      Violation violation(node, new MockRule());
      violationSet->addViolation(violation);
    }
  }
  return CXChildVisit_Recurse;
}

const CXCursor TestCursorUtil::getParmVarDeclCursor(StringSourceCode code) {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(code, index);
  ViolationSet *violationSet = new ViolationSet();
  clang_visitChildren(clang_getTranslationUnitCursor(translationUnit), extractParmVarDeclCursor, violationSet);
  Violation violation = violationSet->getViolations().at(0);
  return violation.cursor;
}

enum CXChildVisitResult extractObjCMethodDecl(CXCursor node, CXCursor parentNode, CXClientData clientData) {
  ViolationSet *violationSet = (ViolationSet *)clientData;
  if (Decl *decl = CursorUtil::getDecl(node)) {
    if (isa<ObjCMethodDecl>(decl)) {
      Violation violation(node, new MockRule());
      violationSet->addViolation(violation);
    }
  }
  return CXChildVisit_Recurse;
}

const CXCursor TestCursorUtil::getObjCMethodDecl(StringSourceCode code) {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit translationUnit = StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(code, index);
  ViolationSet *violationSet = new ViolationSet();
  clang_visitChildren(clang_getTranslationUnitCursor(translationUnit), extractObjCMethodDecl, violationSet);
  Violation violation = violationSet->getViolations().at(0);
  return violation.cursor;
}
