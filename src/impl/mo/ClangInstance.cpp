#include "mo/ClangInstance.h"
#include "mo/Reporter.h"
#include "mo/exception/MOException.h"

ClangInstance::ClangInstance() {
  _index = clang_createIndex(0, 0);
  _translationUnit = NULL;
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

const string ClangInstance::reportDiagnostics(const vector<CXDiagnostic> diagnostics, const Reporter& reporter) {
  return reporter.reportDiagnostics(diagnostics);
}

bool ClangInstance::hasDiagnostics() const {
  return clang_getNumDiagnostics(_translationUnit);
}

const vector<CXDiagnostic> ClangInstance::diagnostics() const {
  vector<CXDiagnostic> diagnostics;
  for (int index = 0, numberOfDiagnostics = clang_getNumDiagnostics(_translationUnit); index < numberOfDiagnostics; index++) {
    diagnostics.push_back(clang_getDiagnostic(_translationUnit, index));
  }
  return diagnostics;
}

const string ClangInstance::reportDiagnostics(const Reporter& reporter) {
  return reportDiagnostics(diagnostics(), reporter);
}

bool ClangInstance::hasWarnings() const {
  return warnings().size();
}

const vector<CXDiagnostic> ClangInstance::warnings() const {
  vector<CXDiagnostic> warnings;
  if (hasDiagnostics()) {
    for (int index = 0, numberOfDiagnostics = clang_getNumDiagnostics(_translationUnit); index < numberOfDiagnostics; index++) {
      CXDiagnostic diagnostic = clang_getDiagnostic(_translationUnit, index);
      if (clang_getDiagnosticSeverity(diagnostic) == CXDiagnostic_Warning) {
        warnings.push_back(diagnostic);
      }
    }
  }
  return warnings;
}

const string ClangInstance::reportWarnings(const Reporter& reporter) {
  return reportDiagnostics(warnings(), reporter);
}

bool ClangInstance::hasErrors() const {
  return errors().size();
}

const vector<CXDiagnostic> ClangInstance::errors() const {
  vector<CXDiagnostic> errors;
  if (hasDiagnostics()) {
    for (int index = 0, numberOfDiagnostics = clang_getNumDiagnostics(_translationUnit); index < numberOfDiagnostics; index++) {
      CXDiagnostic diagnostic = clang_getDiagnostic(_translationUnit, index);
      if (clang_getDiagnosticSeverity(diagnostic) == CXDiagnostic_Error || clang_getDiagnosticSeverity(diagnostic) == CXDiagnostic_Fatal) {
        errors.push_back(diagnostic);
      }
    }
  }
  return errors;
}

const string ClangInstance::reportErrors(const Reporter& reporter) {
  return reportDiagnostics(errors(), reporter);
}

const CXTranslationUnit& ClangInstance::getTranslationUnit() const {
  if (!_translationUnit) {
    throw MOException("No translation unit found, please compile source code first!");
  }
  if (hasErrors()) {
    throw MOException("You are not allowed to get a translation unit with errors!");
  }
  return _translationUnit;
}
