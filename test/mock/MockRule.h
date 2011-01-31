#include "mo/rule/AbstractRule.h"

class MockRule : public AbstractRule {
public:
  void applyStmt(Stmt *stmt) {}
  void applyDecl(Decl *decl) {}

  string name() {
    return "MockRule";
  }
  
  int priority() {
    return 99;
  }

};