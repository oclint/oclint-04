#include <clang/AST/Stmt.h>
#include <clang/AST/Decl.h>

#include "mo/util/RuleUtil.h"

Decl* RuleUtil::getCursorDecl(CXCursor node) {
  if (node.kind >= CXCursor_FirstDecl && node.kind <= CXCursor_LastDecl) {
    return (Decl *)node.data[0];
  }
  return 0;
}

Stmt* RuleUtil::getCursorStmt(CXCursor node) {
  if (node.kind >= CXCursor_FirstStmt && node.kind <= CXCursor_LastStmt) {
    /*
    if (Cursor.kind == CXCursor_ObjCSuperClassRef ||
        Cursor.kind == CXCursor_ObjCProtocolRef ||
        Cursor.kind == CXCursor_ObjCClassRef) {
      return 0;
    }
    */

    return (Stmt *)node.data[1];
  }
  return 0;
}
