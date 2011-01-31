#include "mo/rule/Violation.h"

class MockViolation : public Violation {
public:
  bool indexWithinRange(int index) {
    return indexWithinViolationRange(index);
  }
};