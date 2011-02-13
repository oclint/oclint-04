#include "test/MO_UTIL_FileUtilTest.h"

void FileUtilTest::testFileExists() {
  TS_ASSERT(FileUtil::isSrcExists("test/samples/HelloWorld.m"));
  TS_ASSERT(FileUtil::isSrcExists("test/samples/CompilationFail.txt"));
}

void FileUtilTest::testFileDoesntExist() {
  TS_ASSERT(!FileUtil::isSrcExists(""));
  TS_ASSERT(!FileUtil::isSrcExists("test/samples/CompilationFail.m"));
}
