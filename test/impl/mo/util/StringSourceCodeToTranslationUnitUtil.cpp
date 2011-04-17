#include "mo/util/StringSourceCodeToTranslationUnitUtil.h"

#include <fstream>
using namespace std;

CXTranslationUnit StringSourceCodeToTranslationUnitUtil::compileStringSourceCodeToTranslationUnit(StringSourceCode code, CXIndex index) {
  string tmpFilePath("/tmp/mo.tmp.");
  tmpFilePath += generateRandomString(10) + "." + code.type;
  
  ofstream tmpFile;
  tmpFile.open(tmpFilePath.c_str());
  tmpFile << code.code;
  tmpFile.close();
  
  CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, tmpFilePath.c_str(), 0, 0, 0, 0, CXTranslationUnit_None);
  
  remove(tmpFilePath.c_str());
  
  return translationUnit;
}

char StringSourceCodeToTranslationUnitUtil::generateRandomCharacter() {
  srand(time(NULL));
  static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  return alphanum[rand() % (sizeof(alphanum) - 1)];
}

void StringSourceCodeToTranslationUnitUtil::fillInRandomCharacters(char *pChars, const int lengthOfRandomCharacters) {
  for (int index = 0; index < lengthOfRandomCharacters; ++index) {
    pChars[index] = generateRandomCharacter();
  }
  pChars[lengthOfRandomCharacters] = 0;
}

string StringSourceCodeToTranslationUnitUtil::generateRandomString(int length) {
  char *charsToBeFilled = new char[length + 1];
  fillInRandomCharacters(charsToBeFilled, length);
  return string(charsToBeFilled);
}
