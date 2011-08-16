#ifndef MO_SMELLFINDER_H
#define MO_SMELLFINDER_H

#include <string>

using namespace std;

#include <clang-c/Index.h>

class ViolationSet;
class Reporter;

class SmellFinder {
private:
  ViolationSet *_violationSet;
  
  SmellFinder(const SmellFinder&);
  SmellFinder& operator=(const SmellFinder&);

public:
  SmellFinder();
  virtual ~SmellFinder();
  
  bool hasSmell(const CXTranslationUnit& translationUnit) const;
  const string reportSmells(const Reporter& reporter) const; 
};

#endif
