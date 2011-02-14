#include "mo/exception/MessageBasedException.h"

MessageBasedException::MessageBasedException(string message) {
  _exceptionMessage = message;
}

string MessageBasedException::getMessage() {
  return _exceptionMessage;
}
