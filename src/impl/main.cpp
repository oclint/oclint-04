#include <iostream>

using namespace std;

#include "mo/ClangInstance.h"
#include "mo/SmellFinder.h"
#include "mo/ruleset/RuleSet.h"
#include "mo/exception/MOException.h"

#include "mo/reporter/PlainTextReporter.h"

#include <dlfcn.h>
#include <dirent.h>

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

void dynamicLoadRules(string executablePath, string relativeRulesPath) {
  string absoluteRulesPath = executablePath.substr(0, executablePath.find_last_of("/") + 1) + relativeRulesPath;
  
  DIR *dp;
  struct dirent *dirp;
  string filepath;

  dp = opendir(absoluteRulesPath.c_str());
  if (dp != NULL) {
    while ((dirp = readdir(dp))) {
      if (dirp->d_name[0] != '.') {
        string rulePath = absoluteRulesPath + "/" + dirp->d_name;
        void *ruleHandle = dlopen(rulePath.c_str(), RTLD_NOW);
        if(ruleHandle == NULL){
           cerr << dlerror() << endl;
           exit(-1);
        }
      }
    }
  }
  closedir(dp);
}

int main(int argc, char* argv[]) {
  int execute_flag = -1;
  string executablePath(argv[0]);
  dynamicLoadRules(executablePath, "rules");
  try {
    execute_flag = execute(argv + 1, argc - 1);
  }
  catch (MOException& ex) {
    cout << "Exception: " << ex.message << endl;
  }
  return execute_flag;
}
