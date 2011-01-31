#include <cxxtest/TestSuite.h>
#include "mo/rule/ASTVisitor.h"
#include "test/mock/MockStmt.h"
#include "test/mock/MockDecl.h"

using namespace clang;

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
  
  void testVisitorTraverseStmt() {
    MockStmt stmt;
    TS_ASSERT(visitor->traverse(&stmt));
  }
  
  void testVisitorTraverseDecl() {
    TS_ASSERT(visitor->traverse(new MockDecl()));
  }
};
