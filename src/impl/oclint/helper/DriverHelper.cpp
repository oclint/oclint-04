#include "oclint/helper/DriverHelper.h"

#include <llvm/ADT/SmallString.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/Program.h>
#include <llvm/Support/FileSystem.h>

string getExecutablePath(char *argv) {
  llvm::SmallString<128> installedPath(argv);
  if (llvm::sys::path::filename(installedPath) == installedPath) {
    llvm::sys::Path intermediatePath = llvm::sys::Program::FindProgramByName(
      llvm::sys::path::filename(installedPath.str()));
    if (!intermediatePath.empty()) {
      installedPath = intermediatePath.str();
    }
  }
  llvm::sys::fs::make_absolute(installedPath);
  installedPath = llvm::sys::path::parent_path(installedPath);
  return string(installedPath.c_str());
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

