#include <sys/stat.h> 
#include "mo/util/FileUtil.h"

bool FileUtil::isSrcExists(string srcPath) {
  struct stat statFileInfo;
  return !stat(srcPath.c_str(), &statFileInfo);
}
