#ifndef OCLINT_VIOLATIONSET_H
#define OCLINT_VIOLATIONSET_H

#include <clang-c/Index.h>

#include <string>
#include <vector>

using namespace std;

class Violation;
class Rule;

class ViolationSet {
private:
  vector<Violation> _violations;
  
public:
  void addViolation(const Violation& violation);
  void addViolation(const CXCursor& node, Rule *rule, const string& description = "");
  int numberOfViolations() const;
  const vector<Violation> getViolations() const;
};

#endif
