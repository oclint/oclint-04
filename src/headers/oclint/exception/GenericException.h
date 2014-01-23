#ifndef OCLINT_EXCEPTION_GENERICEXCEPTION_H
#define OCLINT_EXCEPTION_GENERICEXCEPTION_H

#include <string>

using namespace std;

class GenericException
{
public:
  const string message;

  GenericException(const string& exceptionMessage);
};

#endif
