#include <iostream>

using namespace std;

#include "mo/SmellFinder.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "./mo <input file>" << endl;
    return 1;
  }
  string src(argv[1]);
  try {
    SmellFinder smellFinder(src);
    if (!smellFinder.hasSmell()) {
      cout << "No Smell Detected!" << endl;
    }
  }
  catch (char *ex) {
    cout << "Exception: " << ex << endl;
  }
  return 0;
}
