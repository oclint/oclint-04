#ifndef TEST_MOCK_MOCKDECL_H
#define TEST_MOCK_MOCKDECL_H

#include <clang/AST/Decl.h>

using namespace clang;

#include "test/mock/MockDeclContext.h"

class MockDecl : public BlockDecl {
public:
  MockDecl() : BlockDecl(new MockDeclContext(), SourceLocation()) {}
};

#endif
