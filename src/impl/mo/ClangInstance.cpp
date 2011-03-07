#include "mo/ClangInstance.h"
#include "mo/Reporter.h"
#include "mo/exception/MOException.h"

ClangInstance::ClangInstance() {
  _index = clang_createIndex(0, 0);
  _translationUnit = 0;
}

ClangInstance::~ClangInstance() {
  clang_disposeTranslationUnit(_translationUnit); 
  clang_disposeIndex(_index);
}

void ClangInstance::compileSourceFileToTranslationUnit(const char * const * argv, int argc) {
  _translationUnit = clang_parseTranslationUnit(_index, 0, argv, argc, 0, 0, CXTranslationUnit_None);
  if (!_translationUnit) {
    throw MOException("Code compilation fails!");
  }
}

bool ClangInstance::hasDiagnostic() const {
  return clang_getNumDiagnostics(_translationUnit);
}

// Can I return reference of string& here?
const string ClangInstance::reportDiagnostics(const Reporter& reporter) {
  vector<CXDiagnostic> diagnostics;
  for (int index = 0, numberOfDiagnostics = clang_getNumDiagnostics(_translationUnit); index < numberOfDiagnostics; index++) {
    diagnostics.push_back(clang_getDiagnostic(_translationUnit, index));
  }
  return reporter.reportDiagnostics(diagnostics);
}

const CXTranslationUnit& ClangInstance::getTranslationUnit() const {
  if (!_translationUnit) {
    throw MOException("No translation unit found, please compile source code first!");
  }
  if (hasDiagnostic()) {
    throw MOException("You are not allowed to get a questionable translation unit!");
  }
  return _translationUnit;
}
