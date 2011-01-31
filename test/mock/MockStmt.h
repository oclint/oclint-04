#include <clang/AST/Stmt.h>

using namespace clang;

class MockStmt : public Stmt {
public:
  MockStmt() : Stmt(NullStmtClass) {}

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