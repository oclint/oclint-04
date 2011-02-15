#include "mo/SmellFinder.h"
#include "mo/TraverseAST.h"
#include "mo/RuleViolation.h"
#include "mo/util/FileUtil.h"
#include "mo/exception/MessageBasedException.h"

SmellFinder::SmellFinder() {
  _index = clang_createIndex(0, 0);
  _translationUnit = 0;
}

SmellFinder::~SmellFinder() {
  clang_disposeTranslationUnit(_translationUnit); 
  clang_disposeIndex(_index);
}

void SmellFinder::compileSourceFileToTranslationUnit(string src) {
  if (FileUtil::isSrcExists(src)) {
    _translationUnit = clang_parseTranslationUnit(_index, src.c_str(), 0, 0, 0, 0, CXTranslationUnit_None);
    if (!_translationUnit) {
      throw new MessageBasedException("Code compilation fails!");
    }
  }
  else {
    throw new MessageBasedException("File doesn't exist!");
  }
}

bool SmellFinder::hasSmell(string src) {
  compileSourceFileToTranslationUnit(src);
  RuleViolation *violation = new RuleViolation();
  clang_visitChildren(clang_getTranslationUnitCursor(_translationUnit), traverseAST, violation);
  return violation->numberOfViolations();
}
