#ifndef MO_EXCEPTION_MOEXCEPTION_H
#define MO_EXCEPTION_MOEXCEPTION_H

#include <string>

using namespace std;

class MOException {
private:
  string _exceptionMessage;
  
public:
  MOException(const string& message);
  const string& getMessage();
};

#endif
