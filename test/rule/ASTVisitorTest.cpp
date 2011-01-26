#include <gtest/gtest.h>
#include "mo/rule/ASTVisitor.h"

TEST(ASTVisitorTest, fire_the_gcov) {
  SourceLocation loc;
  NullStmt stmt(loc);
  ASTVisitor *visitor = new ASTVisitor();
  EXPECT_TRUE(visitor->traverse(&stmt));
}
