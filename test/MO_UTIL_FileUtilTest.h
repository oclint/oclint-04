#include <cxxtest/TestSuite.h>
#include "mo/util/FileUtil.h"

class FileUtilTest : public CxxTest::TestSuite { 
public:
  void testFileExists();
  void testFileDoesntExist();
};
