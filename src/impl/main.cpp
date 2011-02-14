#include <iostream>

using namespace std;

#include "mo/SmellFinder.h"
#include "mo/exception/MessageBasedException.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "./mo <input file>" << endl;
    return 1;
  }
  string src(argv[1]);
  try {
    SmellFinder smellFinder;
    if (!smellFinder.hasSmell(src)) {
      cout << "No Smell Detected!" << endl;
    }
  }
  catch (MessageBasedException *ex) {
    cout << "Exception: " << ex->getMessage() << endl;
  }
  return 0;
}
