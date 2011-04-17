#ifndef MO_UTIL_STRINGSOURCECODETOTRANSLATIONUNITUTIL_H
#define MO_UTIL_STRINGSOURCECODETOTRANSLATIONUNITUTIL_H

#include "mo/StringSourceCode.h"

#include <string>
using namespace std;

#include <clang-c/Index.h>

class StringSourceCodeToTranslationUnitUtil {
public:
  static CXTranslationUnit compileStringSourceCodeToTranslationUnit(StringSourceCode code, CXIndex index);
  
private:
  static char generateRandomCharacter();
  static void fillInRandomCharacters(char *pChars, const int lengthOfRandomCharacters);
  static string generateRandomString(int length);
};

#endif
