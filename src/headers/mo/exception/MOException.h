#ifndef MO_EXCEPTION_MOEXCEPTION_H
#define MO_EXCEPTION_MOEXCEPTION_H

#include <string>

using namespace std;

class MOException {
private:
  string _exceptionMessage;
  
public:
  MOException(string message);
  string getMessage();
};

#endif
