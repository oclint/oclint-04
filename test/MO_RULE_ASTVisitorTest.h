#include <cxxtest/TestSuite.h>
#include "mo/rule/ASTVisitor.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/Decl.h>

using namespace clang;

#include "test/mock/MockDecl.h"
#include "test/mock/MockStmt.h"

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
