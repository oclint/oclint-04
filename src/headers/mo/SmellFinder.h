#ifndef MO_SMELLFINDER_H
#define MO_SMELLFINDER_H

#include <string>
#include <vector>

using namespace std;

#include <clang-c/Index.h>

class RuleData;

class SmellFinder {
private:
  CXIndex _index;
  CXTranslationUnit _translationUnit;
  RuleData *_data;

public:
  SmellFinder();
  ~SmellFinder();
  
  void compileSourceFileToTranslationUnit(string src);
  bool hasSmell(string src);
  string smellToString(); 
};

#endif
