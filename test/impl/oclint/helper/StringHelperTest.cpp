#include "oclint/helper/StringHelperTest.h"
#include "oclint/helper/StringHelper.h"

void StringHelperTest::testOneDigitNumber() {
  TS_ASSERT_EQUALS(StringHelper::convertIntToString(1), "1");
}

void StringHelperTest::testTwoDigitsNumber() {
  TS_ASSERT_EQUALS(StringHelper::convertIntToString(12), "12");
}

void StringHelperTest::testFiveDigitsNumber() {
  TS_ASSERT_EQUALS(StringHelper::convertIntToString(12345), "12345");
}

