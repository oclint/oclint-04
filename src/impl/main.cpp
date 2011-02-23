#include <iostream>

using namespace std;

#include "mo/SmellFinder.h"
#include "mo/exception/MOException.h"

int execute(const char * const * argv, int argc) {
  SmellFinder smellFinder;
  smellFinder.compileSourceFileToTranslationUnit(argv, argc);
  if (smellFinder.hasDiagnostic()) {
    cout << smellFinder.diagnosticToString() << endl;
    return 1;
  }
  if (smellFinder.hasSmell()) {
    cout << smellFinder.smellToString() << endl;
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
