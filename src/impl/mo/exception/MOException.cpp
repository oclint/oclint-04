#include "mo/exception/MOException.h"

MOException::MOException(const string& message) {
  _exceptionMessage = message;
}

const string& MOException::getMessage() {
  return _exceptionMessage;
}
