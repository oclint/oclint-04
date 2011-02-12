#ifndef MO_RULE_ASTVISITOR_H
#define MO_RULE_ASTVISITOR_H

#include <string>
#include <vector>

using namespace std;

#include <clang-c/Index.h>

class SmellFinder {
public:
  bool hasSmell(string src);
};

#endif
