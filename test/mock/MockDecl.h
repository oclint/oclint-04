#include <clang/AST/Decl.h>

using namespace clang;

class MockDeclContext : public DeclContext {
public:
  MockDeclContext() : DeclContext(Decl::Var) {}
};

class MockDecl : public BlockDecl {
public:
  MockDecl() : BlockDecl(new MockDeclContext(), SourceLocation()) {}
};