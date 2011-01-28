#include <cxxtest/TestSuite.h>

class CanaryTest : public CxxTest::TestSuite { 
public:
  void testCanary() {
    TS_ASSERT(true);
  }
};
