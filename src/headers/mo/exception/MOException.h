#ifndef MO_EXCEPTION_MOEXCEPTION_H
#define MO_EXCEPTION_MOEXCEPTION_H

#include <string>

using namespace std;

class MOException {
public:    
  const string message;
  
  MOException(const string& exceptionMessage);
};

#endif
