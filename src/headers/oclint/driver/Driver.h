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

class Driver {
public:
  static int main(int argc, char* argv[]);

private:
  static int dynamicLoadRules(string ruleDirPath);
  static int consumeArgRulesPath(char* executablePath);
  static void consumeOptArgument(string argKey, string argValue, vector<string>& argVector);
  static void consumeListArgument(string argKey, vector<string> argValues, vector<string>& argVector);
  static void consumeOptArguments(vector<string>& argVector);
  static void consumeListArguments(vector<string>& argVector);
  static void consumeRuleConfigurations();

  static vector<string> getCompilerArguments();
  static Reporter* reporter();
  static int reportSmells(ClangInstance& instance, ostream& out);
  static int executeFile(int argc, char** argv, ostream& out);
  static int execute(ostream& out);
  static ostream* outStream();
  static void disposeOutStream(ostream* out);
};

#endif

