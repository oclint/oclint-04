#include <cxxtest/TestSuite.h>
#include "mo/rule/ASTVisitor.h"

class ASTVisitorTest : public CxxTest::TestSuite { 
private:
  ASTVisitor *visitor;
public:
  void setUp() {
    visitor = new ASTVisitor();
  }
  
  void tearDown() {
    delete visitor;
  }
  
  void testFireGCov() {
    SourceLocation loc;
    NullStmt stmt(loc);
    TS_ASSERT(visitor->traverse(&stmt));
  }
};
