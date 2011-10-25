#include <dlfcn.h>
#include <dirent.h>
#include <iostream>

#include "oclint/ClangInstance.h"
#include "oclint/SmellFinder.h"
#include "oclint/RuleSet.h"
#include "oclint/exception/GenericException.h"
#include "oclint/reporter/PlainTextReporter.h"

using namespace std;

int dynamicLoadRules(string executablePath, string relativeRulesPath) {
  string absoluteRulesPath = executablePath.substr(0, executablePath.find_last_of("/") + 1) + relativeRulesPath;
  
  DIR *dp;
  struct dirent *dirp;

  dp = opendir(absoluteRulesPath.c_str());
  if (dp != NULL) {
    while ((dirp = readdir(dp))) {
      if (dirp->d_name[0] != '.') {
        string rulePath = absoluteRulesPath + "/" + dirp->d_name;
        void *ruleHandle = dlopen(rulePath.c_str(), RTLD_NOW);
        if(ruleHandle == NULL){
           cerr << dlerror() << endl;
           closedir(dp);
           return 3;
        }
      }
    }
    closedir(dp);
  }
  return 0;
}

int reportSmells(ClangInstance& instance, PlainTextReporter& reporter) {
  int numberOfSmells = 0;
  if (instance.hasWarnings()) {
    cout << instance.reportWarnings(reporter);
    numberOfSmells -= instance.warnings().size();
  }
  SmellFinder smellFinder;
  if (smellFinder.hasSmell(instance.getTranslationUnit())) {
    cout << smellFinder.reportSmells(reporter);
    numberOfSmells -= smellFinder.numberOfViolations();
  }
  return numberOfSmells;
}

int execute(const char * const * argv, int argc) {
  PlainTextReporter reporter;
  ClangInstance instance;
  instance.compileSourceFileToTranslationUnit(argv, argc);
  if (instance.hasErrors()) {
    cout << instance.reportErrors(reporter);
    return 1;
  }
  return reportSmells(instance, reporter);
}

int main(int argc, char* argv[]) {
  int execute_flag = 99;
  string executablePath(argv[0]);
  execute_flag = dynamicLoadRules(executablePath, "rules");
  if (execute_flag == 0) {
    try {
      execute_flag = execute(argv + 1, argc - 1);
    }
    catch (GenericException& ex) {
      cout << "Exception: " << ex.message << endl;
    }
  }
  return execute_flag;
}
