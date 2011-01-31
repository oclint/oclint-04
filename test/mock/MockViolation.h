#ifndef TEST_MOCK_MOCKVIOLATION_H
#define TEST_MOCK_MOCKVIOLATION_H

#include "mo/rule/Violation.h"

class MockViolation : public Violation {
public:
  bool indexWithinRange(int index) {
    return indexWithinViolationRange(index);
  }
};

#endif
