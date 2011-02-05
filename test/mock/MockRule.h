#ifndef TEST_MOCK_MOCKRULE_H
#define TEST_MOCK_MOCKRULE_H

#include "mo/rule/AbstractRule.h"
#include "mo/rule/Violation.h"

class MockRule : public AbstractRule {
public:
  void applyStmt(Stmt *stmt, Violation *violation) {
    violation->addViolation(createRuleViolation("statement"));
  }
  
  void applyDecl(Decl *decl, Violation *violation) {
    violation->addViolation(createRuleViolation("declaration"));
  }

  string name() {
    return "MockRule";
  }
  
  int priority() {
    return 99;
  }
  
private:
  RuleViolation *createRuleViolation(string type) {
    return new RuleViolation(SourceRange(SourceLocation(), SourceLocation()), 
      this, "violate " + type + " when applying mock rule");
  }
};

#endif
