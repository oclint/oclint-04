#ifndef TEST_MOCK_MOCKDECLCONTEXT_H
#define TEST_MOCK_MOCKDECLCONTEXT_H

#include <clang/AST/Decl.h>

using namespace clang;

class MockDeclContext : public DeclContext {
public:
  MockDeclContext() : DeclContext(Decl::Var) {}
};

#endif
