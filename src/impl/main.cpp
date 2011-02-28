#include <iostream>

using namespace std;

#include "mo/ClangInstance.h"
#include "mo/SmellFinder.h"
#include "mo/exception/MOException.h"

#include "mo/reporter/PlainTextReporter.h"

int execute(const char * const * argv, int argc) {
  PlainTextReporter reporter;
  ClangInstance instance;
  instance.compileSourceFileToTranslationUnit(argv, argc);
  if (instance.hasDiagnostic()) {
    cout << instance.reportDiagnostics(reporter);
    return 1;
  }
  SmellFinder smellFinder;
  if (smellFinder.hasSmell(instance.getTranslationUnit())) {
    cout << smellFinder.reportSmells(reporter);
    return 2;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  int execute_flag = -1;
  try {
    execute_flag = execute(argv + 1, argc - 1);
  }
  catch (MOException& ex) {
    cout << "Exception: " << ex.message << endl;
  }
  return execute_flag;
}
