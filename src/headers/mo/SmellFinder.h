#ifndef MO_SMELLFINDER_H
#define MO_SMELLFINDER_H

#include <string>

using namespace std;

#include <clang-c/Index.h>

class RuleData;
class Reporter;

class SmellFinder {
private:
  RuleData *_data;

public:
  SmellFinder();
  ~SmellFinder();
  
  bool hasSmell(CXTranslationUnit translationUnit);
  const string reportSmells(const Reporter& reporter); 
};

#endif
