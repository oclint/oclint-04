#include "mo/SmellFinder.h"

SmellFinder::SmellFinder(string src) {
  _index = clang_createIndex(0, 0);
  _translationUnit = clang_parseTranslationUnit(_index, src.c_str(), 0, 0, 0, 0, CXTranslationUnit_None);
}

SmellFinder::~SmellFinder() {
  clang_disposeTranslationUnit(_translationUnit); 
  clang_disposeIndex(_index);
}

bool SmellFinder::hasSmell() {
  return false;
}
