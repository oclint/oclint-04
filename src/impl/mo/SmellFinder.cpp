#include "mo/SmellFinder.h"
#include "mo/TraverseAST.h"
#include "mo/Reporter.h"
#include "mo/Rule.h"
#include "mo/RuleViolation.h"
#include "mo/RuleData.h"
#include "mo/exception/MOException.h"

SmellFinder::SmellFinder() {
  _data = new RuleData();
}

SmellFinder::~SmellFinder() {
  delete _data;
}

bool SmellFinder::hasSmell(const CXTranslationUnit& translationUnit) const {
  if (!translationUnit) {
    throw MOException("Inspect on an mpty translation unit!");
  }
  if (clang_getNumDiagnostics(translationUnit)) {
    throw MOException("Insepct on a questionable translation unit!");
  }
  clang_visitChildren(clang_getTranslationUnitCursor(translationUnit), traverseAST, _data);
  return _data->numberOfViolations();
}

const string SmellFinder::reportSmells(const Reporter& reporter) const {
  return reporter.reportViolations(_data->getViolations());
}
