#include "oclint/version.h"
#include "oclint/helper/StringHelper.h"

#define LLVM_VERSION_MAJOR   3
#define LLVM_VERSION_MINOR   1

#define OCLINT_VERSION_MAJOR 0
#define OCLINT_VERSION_MINOR 4
#define OCLINT_VERSION_PATCH 3

string llvm_version() {
  return StringHelper::convertIntToString(LLVM_VERSION_MINOR) + "." + StringHelper::convertIntToString(LLVM_VERSION_MINOR);
}

string oclint_version() {
  return StringHelper::convertIntToString(OCLINT_VERSION_MAJOR) + "." + StringHelper::convertIntToString(OCLINT_VERSION_MINOR) + "." + StringHelper::convertIntToString(OCLINT_VERSION_PATCH);
}
