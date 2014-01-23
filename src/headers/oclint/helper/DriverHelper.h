#ifndef OCLINT_HELPER_DRIVERHELPER_H
#define OCLINT_HELPER_DRIVERHELPER_H

#include <string>
#include <vector>

using namespace std;

string getExecutablePath(char *argv);
char* safeCStr(string str);
char** getArgv(vector<string> argVector, string input);

#endif

