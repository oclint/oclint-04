#include "mo/exception/MOException.h"

MOException::MOException(string message) {
  _exceptionMessage = message;
}

string MOException::getMessage() {
  return _exceptionMessage;
}
