#include "oclint/exception/GenericExceptionTest.h"

void GenericExceptionTest::testGetExceptionMessage() {
  GenericException exception("an exception message for test");
  TS_ASSERT_EQUALS(exception.message, "an exception message for test");
}
