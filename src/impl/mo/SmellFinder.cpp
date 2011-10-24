#include "mo/SmellFinder.h"
#include "mo/Reporter.h"
#include "mo/Violation.h"
#include "mo/ViolationSet.h"
#include "mo/exception/MOException.h"
#include "mo/RuleSet.h"
#include "mo/util/CursorUtil.h"

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
