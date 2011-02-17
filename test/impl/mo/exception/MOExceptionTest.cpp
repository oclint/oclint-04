#include "mo/exception/MOExceptionTest.h"

void MOExceptionTest::testGetExceptionMessage() {
  MOException *exception = new MOException("an exception message for test");
  TS_ASSERT_EQUALS(exception->getMessage(), "an exception message for test");
}
