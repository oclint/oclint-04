#ifndef OCLINT_DRIVER_DRIVER_H
#define OCLINT_DRIVER_DRIVER_H

#include <dlfcn.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ClangInstance;
class Reporter;
class Benchmark;

class Driver {
public:
  int main(int argc, char* argv[]);

private:
  Benchmark *_benchmark;

private:
  int dynamicLoadRules(string ruleDirPath);
  int loadRulesFromDefaultRulePath(char* executablePath);
  int loadRulesFromCustomRulePaths();
  int consumeArgRulesPath(char* executablePath);
  void consumeOptArgument(string argKey, string argValue, vector<string>& argVector);
  void consumeListArgument(string argKey, vector<string> argValues, vector<string>& argVector);
  void consumeOptArguments(vector<string>& argVector);
  void consumeListArguments(vector<string>& argVector);
  void consumeRuleConfigurations();

  vector<string> getCompilerArguments();
  Reporter* reporter();
  int reportSmells(ClangInstance& instance, ostream& out);
  int executeFile(int argc, char** argv, ostream& out);
  int execute(ostream& out);
  ostream* outStream();
  void disposeOutStream(ostream* out);
  void dumpBenchmarks();
};

#endif

