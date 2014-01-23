#include "oclint/helper/StringHelper.h"

#include <sstream>

using namespace std;

string StringHelper::convertIntToString(int number)
{
  stringstream buffer;
  buffer << number;
  return buffer.str();
}
