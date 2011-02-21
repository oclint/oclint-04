#include "mo/SmellFinder.h"
#include "mo/TraverseAST.h"
#include "mo/Rule.h"
#include "mo/RuleViolation.h"
#include "mo/RuleData.h"
#include "mo/exception/MOException.h"

#include "mo/rule/SwitchStatementRule.h"

SmellFinder::SmellFinder() {
  _index = clang_createIndex(0, 0);
  _translationUnit = 0;
  _data = new RuleData();
  
  // temporarily use a fixed Rule
  _data->setRule(new SwitchStatementRule());
}

SmellFinder::~SmellFinder() {
  clang_disposeTranslationUnit(_translationUnit); 
  clang_disposeIndex(_index);
  delete _data;
}

void SmellFinder::compileSourceFileToTranslationUnit(char* argv[], int argc) {
  _translationUnit = clang_parseTranslationUnit(_index, 0, argv, argc, 0, 0, CXTranslationUnit_None);
  if (!_translationUnit) {
    throw MOException("Code compilation fails!");
  }
}

bool SmellFinder::hasSmell(char* argv[], int argc) {
  compileSourceFileToTranslationUnit(argv, argc);
  clang_visitChildren(clang_getTranslationUnitCursor(_translationUnit), traverseAST, _data);
  return _data->numberOfViolations();
}

string SmellFinder::smellToString() {
  // later extract violations from RuleData, and generate violation report
  return "Smell Detected!";
}
