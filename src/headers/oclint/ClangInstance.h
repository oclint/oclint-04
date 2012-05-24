#ifndef OCLINT_CLANGINSTANCE_H
#define OCLINT_CLANGINSTANCE_H

#include <string>
#include <vector>

#include <clang-c/Index.h>

class Reporter;

using namespace std;

class ClangInstance {
private:
  CXIndex _index;
  CXTranslationUnit _translationUnit;
  
  ClangInstance(const ClangInstance&);
  ClangInstance& operator=(const ClangInstance&);
  
  const string reportDiagnostics(
    const vector<CXDiagnostic> diagnostics, const Reporter& reporter);

public:
  ClangInstance();
  virtual ~ClangInstance();
  
  void compileSourceFileToTranslationUnit(const char * const * argv, int argc);
  bool hasDiagnostics() const;
  const vector<CXDiagnostic> diagnostics() const;
  const string reportDiagnostics(const Reporter& reporter);
  bool hasWarnings() const;
  const vector<CXDiagnostic> warnings() const;
  const string reportWarnings(const Reporter& reporter);
  bool hasErrors() const;
  const vector<CXDiagnostic> errors() const;
  const string reportErrors(const Reporter& reporter);
  const CXTranslationUnit& getTranslationUnit() const;
};

#endif
