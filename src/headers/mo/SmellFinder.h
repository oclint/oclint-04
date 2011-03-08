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
  
  SmellFinder(const SmellFinder& finder);
  SmellFinder& operator=(const SmellFinder& otherFinder);

public:
  SmellFinder();
  ~SmellFinder();
  
  bool hasSmell(const CXTranslationUnit& translationUnit) const;
  const string reportSmells(const Reporter& reporter) const; 
};

#endif
