#ifndef MO_TRAVERSEAST_H
#define MO_TRAVERSEAST_H

#include <clang-c/Index.h>

enum CXChildVisitResult traverseAST(CXCursor node, CXCursor parentNode, CXClientData clientData);

#endif
