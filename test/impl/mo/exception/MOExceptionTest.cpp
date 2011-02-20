#include "mo/exception/MOExceptionTest.h"

void MOExceptionTest::testGetExceptionMessage() {
  MOException exception("an exception message for test");
  TS_ASSERT_EQUALS(exception.message, "an exception message for test");
}
