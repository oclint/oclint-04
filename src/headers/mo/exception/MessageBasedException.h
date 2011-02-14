#ifndef MO_EXCEPTION_MESSAGEBASEDEXCEPTION_H
#define MO_EXCEPTION_MESSAGEBASEDEXCEPTION_H

#include <string>

using namespace std;

class MessageBasedException {
private:
  string _exceptionMessage;
  
public:
  MessageBasedException(string message);
  string getMessage();
};

#endif
