#include "oclint/SmellFinder.h"
#include "oclint/Reporter.h"
#include "oclint/Violation.h"
#include "oclint/ViolationSet.h"
#include "oclint/exception/GenericException.h"
#include "oclint/RuleSet.h"
#include "oclint/util/CursorUtil.h"

SmellFinder::SmellFinder() {
  _violationSet = new ViolationSet();
}

SmellFinder::~SmellFinder() {
  delete _violationSet;
}

bool SmellFinder::hasSmell(const CXTranslationUnit& translationUnit) const {
  if (!translationUnit) {
    throw GenericException("Inspect on an empty translation unit!");
  }
  clang_visitChildrenWithBlock(clang_getTranslationUnitCursor(translationUnit), ^(CXCursor node, CXCursor parentNode) {
    if (CursorUtil::isCursorDeclaredInCurrentFile(node)) {
      RuleSet::apply(node, parentNode, *_violationSet);
    }
    return CXChildVisit_Recurse;
  });
  return numberOfViolations();
}

int SmellFinder::numberOfViolations() const {
  return _violationSet->numberOfViolations();
}

const string SmellFinder::reportSmells(const Reporter& reporter) const {
  return reporter.reportViolations(_violationSet->getViolations());
}
