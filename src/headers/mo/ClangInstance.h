#ifndef MO_CLANGINSTANCE_H
#define MO_CLANGINSTANCE_H

#include <string>
#include <vector>

using namespace std;

#include <clang-c/Index.h>

class Reporter;

class ClangInstance {
private:
  CXIndex _index;
  CXTranslationUnit _translationUnit;

public:
  ClangInstance();
  ~ClangInstance();
  
  void compileSourceFileToTranslationUnit(const char * const * argv, int argc);
  bool hasDiagnostic();
  const string reportDiagnostics(const Reporter& reporter);
  CXTranslationUnit getTranslationUnit();
};

#endif
