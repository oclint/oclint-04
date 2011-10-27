#include <dlfcn.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "oclint/ClangInstance.h"
#include "oclint/SmellFinder.h"
#include "oclint/RuleSet.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/exception/GenericException.h"
#include "oclint/reporter/PlainTextReporter.h"
#include "oclint/reporter/HTMLReporter.h"
#include "oclint/driver/CommandLineOptions.h"

using namespace std;

static void versionPrinter() {
  cout << "OCLint (http://oclint.org/):" << endl
    << "  oclint version 0.2.4" << endl
    << "  llvm version 3.0" << endl;
}

static void parseCommandLineOptions(int argc, char* argv[]) {
  cl::SetVersionPrinter(versionPrinter);
  cl::ParseCommandLineOptions(argc, argv, 
    "OCLint, a static code analysis tool for Objective-C and related languages\n");
}

int dynamicLoadRules(string ruleDirPath) {
  DIR *dp = opendir(ruleDirPath.c_str());
  if (dp != NULL) {
    struct dirent *dirp;
    while ((dirp = readdir(dp))) {
      if (dirp->d_name[0] == '.') {
        continue;
      }
      string rulePath = ruleDirPath + "/" + string(dirp->d_name);
      if (dlopen(rulePath.c_str(), RTLD_NOW) == NULL){
        cerr << dlerror() << endl;
        closedir(dp);
        return 3;
      }
    }
    closedir(dp);
  }
  return 0;
}

int consumeArgRulesPath(char* executablePath) {
  if (argRulesPath.size() == 0) {
    string exeStrPath(executablePath);
    string defaultRulePath = exeStrPath.substr(0, exeStrPath.find_last_of("/") + 1) + "rules";
    return dynamicLoadRules(defaultRulePath);
  }
  int returnFlag = 0;
  for (unsigned i = 0; i < argRulesPath.size() && returnFlag == 0; ++i) {
    returnFlag = dynamicLoadRules(argRulesPath[i]);
  }
  return returnFlag;
}

void consumeOptArgument(string argKey, string argValue, vector<string>& argVector) {
  if (argValue != "-") {
    argVector.push_back("-" + argKey);
    argVector.push_back(argValue);
  }
}

void consumeListArgument(string argKey, vector<string> argValues, vector<string>& argVector) {
  for (unsigned i = 0; i < argValues.size(); ++i) {
    argVector.push_back("-" + argKey);
    argVector.push_back(argValues[i]);
  }
}

void consumeOptArguments(vector<string>& argVector) {
  consumeOptArgument("x", argLanguageType, argVector);
  consumeOptArgument("arch", argArch, argVector);
  consumeOptArgument("isysroot", argSysroot, argVector);
}

void consumeListArguments(vector<string>& argVector) {
  consumeListArgument("D", argMacros, argVector);
  consumeListArgument("F", argFrameworkSearchPath, argVector);
  consumeListArgument("include", argIncludes, argVector);
  consumeListArgument("I", argIncludeSearchPath, argVector);
}

void consumeRuleConfigurations() {
  for (unsigned i = 0; i < argRuleConfiguration.size(); ++i) {
    string configuration = argRuleConfiguration[i];
    int indexOfSeparator = configuration.find_last_of("=");
    string key = configuration.substr(0, indexOfSeparator);
    string value = configuration.substr(indexOfSeparator + 1, configuration.size() - indexOfSeparator - 1);
    RuleConfiguration::addConfiguration(key, value);
  }
}

vector<string> getCompilerArguments() {
  vector<string> argv;
  consumeOptArguments(argv);
  consumeListArguments(argv);
  consumeRuleConfigurations();
  return argv;
}

char* safeCStr(string str) {
  char *argv = new char[str.size() + 1];
  strncpy(argv, str.c_str(), str.size());
  argv[str.size()] = '\0';
  return argv;
}

char** getArgv(vector<string> argVector, string input) {
  char** argv = new char*[argVector.size() + 1];
  unsigned i;
  for (i = 0; i < argVector.size(); i++) {
    argv[i] = safeCStr(argVector[i]);
  }
  argv[i] = safeCStr(input);
  return argv;
}

Reporter* reporter() {
  if (argReportType == html) {
    return new HTMLReporter();
  }
  return new PlainTextReporter();
}

int reportSmells(ClangInstance& instance, ostream& out) {
  int numberOfSmells = 0;
  if (instance.hasWarnings()) {
    out << instance.reportWarnings(*reporter());
    numberOfSmells += instance.warnings().size();
  }
  SmellFinder smellFinder;
  if (smellFinder.hasSmell(instance.getTranslationUnit())) {
    out << smellFinder.reportSmells(*reporter());
    numberOfSmells += smellFinder.numberOfViolations();
  }
  return numberOfSmells;
}

int executeFile(int argc, char** argv, ostream& out) {
  ClangInstance instance;
  instance.compileSourceFileToTranslationUnit(argv, argc);
  if (instance.hasErrors()) {
    out << instance.reportErrors(*reporter());
    return instance.errors().size();
  }
  return reportSmells(instance, out);
}

int execute(ostream& out) {
  vector<string> argVector = getCompilerArguments();
  int argc = argVector.size() + 1;
  int totalNumberOfSmells = 0;
  for (unsigned i = 0; i < argInputs.size(); i++) {
    char** argv = getArgv(argVector, argInputs[i]);
    totalNumberOfSmells += executeFile(argc, argv, out);
  }
  return totalNumberOfSmells;
}

ostream* outStream() {
  if (argOutput == "-") {
    return &cout;
  }
  ofstream *out = new ofstream(argOutput.c_str());
  if (!out->is_open()) {
    throw GenericException("Cannot open file " + argOutput);
  }
  return out;
}

void disposeOutStream(ostream* out) {
  if (out && argOutput != "-") {
    ofstream *fout = (ofstream *)out;
    fout->close();
  }
}

int main(int argc, char* argv[]) {
  ostream *out;
  parseCommandLineOptions(argc, argv);
  if (consumeArgRulesPath(argv[0]) == 0 && RuleSet::numberOfRules() > 0) {
    try {
      out = outStream();
      int returnValue = execute(*out);
      disposeOutStream(out);
      return returnValue;
    }
    catch (GenericException& ex) {
      cerr << "Exception: " << ex.message << endl;
      return -3;
    }
  }
  else {
    cerr << "No rule found" << endl;
    return -2;
  }
  return -1;
}
