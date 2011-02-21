#include <iostream>

using namespace std;

#include "mo/SmellFinder.h"
#include "mo/exception/MOException.h"

int main(int argc, char* argv[]) {
  try {
    SmellFinder smellFinder;
    if (smellFinder.hasSmell(argv, argc)) {
      cout << smellFinder.smellToString() << endl;
    }
    else {
      cout << "No Smell Detected!" << endl;
    }
  }
  catch (MOException& ex) {
    cout << "Exception: " << ex.message << endl;
  }
  return 0;
}
