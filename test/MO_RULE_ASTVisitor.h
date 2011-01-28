#include <cxxtest/TestSuite.h>
#include "mo/rule/ASTVisitor.h"

#include <clang/AST/Stmt.h>
#include <clang/AST/DeclBase.h>

using namespace clang;

class TestStmt : public Stmt {
public:
  TestStmt() : Stmt(NullStmtClass) {}

public:  
  child_iterator child_begin() {
    return StmtIterator();
  }
  
  child_iterator child_end() {
    return StmtIterator();
  }
  
  SourceRange getSourceRange() const {
    return SourceRange(SourceLocation(), SourceLocation());
  }
};

class TestDeclContext : public DeclContext {
public:
  TestDeclContext() : DeclContext(Decl::Var) {}
};

class TestDecl : public Decl {
public:
  TestDecl() : Decl(Var, new TestDeclContext(), SourceLocation()) {}
};

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
    TestStmt stmt;
    TS_ASSERT(visitor->traverse(&stmt));
  }
  
  void testVisitorTraverseDecl() {
    TS_ASSERT(!visitor->traverse(new TestDecl()));
  }
};
