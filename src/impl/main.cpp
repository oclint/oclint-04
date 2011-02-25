#include <iostream>

using namespace std;

#include "mo/SmellFinder.h"
#include "mo/exception/MOException.h"

#include "mo/reporter/PlainTextReporter.h"

int execute(const char * const * argv, int argc) {
  PlainTextReporter reporter;
  SmellFinder smellFinder;
  smellFinder.compileSourceFileToTranslationUnit(argv, argc);
  if (smellFinder.hasDiagnostic()) {
    cout << smellFinder.reportDiagnostics(reporter);
    return 1;
  }
  if (smellFinder.hasSmell()) {
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
