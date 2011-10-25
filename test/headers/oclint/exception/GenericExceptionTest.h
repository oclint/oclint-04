#include <cxxtest/TestSuite.h>
#include "oclint/exception/GenericException.h"

class GenericExceptionTest : public CxxTest::TestSuite { 
public:
  void testGetExceptionMessage();
};
