#include "mo/rule/SwitchStatementRule.h"
#include "mo/RuleViolation.h"

#include <clang/AST/Stmt.h>

using namespace clang;

#include <iostream>
#include <sstream>

void SwitchStatementRule::apply(CXCursor node, CXCursor parentNode, RuleViolation& violation) {
  if (node.kind >= CXCursor_FirstStmt && node.kind <= CXCursor_LastStmt) {
    Stmt *stmt = (Stmt *) node.data[1];
    if (stmt && isa<SwitchStmt>(stmt)) {
      CXSourceLocation loc = clang_getCursorLocation(node);
      CXFile file;
      unsigned line, column, offset;
      clang_getSpellingLocation(loc, &file, &line, &column, &offset);
      CXString source = clang_getFileName(file);
      if (!clang_getCString(source)) {
        clang_disposeString(source);
        return;
      }
      else {
        const char *cstrSource = clang_getCString(source);
        clang_disposeString(source);
        stringstream streamViolation;
        streamViolation << name() << " - " << cstrSource << ":" << line << ":" << column << ":" << offset;
        violation.addViolation(streamViolation.str());
      }
    }
  }
}

const string SwitchStatementRule::name() {
  return "Switch Statement";
}
