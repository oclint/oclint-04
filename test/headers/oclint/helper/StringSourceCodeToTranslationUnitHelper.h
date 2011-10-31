#ifndef OCLINT_HELPER_STRINGSOURCECODETOTRANSLATIONUNITHELPER_H
#define OCLINT_HELPER_STRINGSOURCECODETOTRANSLATIONUNITHELPER_H

#include "oclint/StringSourceCode.h"

#include <string>
using namespace std;

#include <clang-c/Index.h>

class StringSourceCodeToTranslationUnitHelper {
public:
  static CXTranslationUnit compileStringSourceCodeToTranslationUnit(StringSourceCode code, CXIndex index);
  static int lengthOfTmpFileName(StringSourceCode code);
  
private:
  static char generateRandomCharacter();
  static void fillInRandomCharacters(char *pChars, const int lengthOfRandomCharacters);
  static string generateRandomString(int length);
  static string generateTmpFileName(StringSourceCode code);
};

#endif
