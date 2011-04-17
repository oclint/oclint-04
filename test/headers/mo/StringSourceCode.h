#ifndef MO_STRINGSOURCECODE_H
#define MO_STRINGSOURCECODE_H

#include <string>
using namespace std;

class StringSourceCode {
public:
  const string code;
  const string type;

  StringSourceCode(const string& srcCode, const string& srcType) : code(srcCode), type(srcType) { }
};

#endif
