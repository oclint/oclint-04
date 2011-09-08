#include "mo/SmellFinder.h"
#include "mo/TraverseAST.h"
#include "mo/Reporter.h"
#include "mo/Violation.h"
#include "mo/ViolationSet.h"
#include "mo/exception/MOException.h"

SmellFinder::SmellFinder() {
  _violationSet = new ViolationSet();
}

SmellFinder::~SmellFinder() {
  delete _violationSet;
}

bool SmellFinder::hasSmell(const CXTranslationUnit& translationUnit) const {
  if (!translationUnit) {
    throw MOException("Inspect on an empty translation unit!");
  }
  if (clang_getNumDiagnostics(translationUnit)) {
    throw MOException("Insepct on a questionable translation unit!");
  }
  clang_visitChildren(clang_getTranslationUnitCursor(translationUnit), traverseAST, _violationSet);
  return _violationSet->numberOfViolations();
}

const string SmellFinder::reportSmells(const Reporter& reporter) const {
  return reporter.reportViolations(_violationSet->getViolations());
}
