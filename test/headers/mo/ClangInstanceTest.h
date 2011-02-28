#include <cxxtest/TestSuite.h>
#include "mo/ClangInstance.h"

class ClangInstanceTest : public CxxTest::TestSuite { 
private:
  ClangInstance *instance;
  
public:
  void setUp();
  void tearDown();
  void testHasNoDiagnostic();
  void testHasDiagnostic();
  void testCodeCompilationFailException();
  void testReportDiagnostics();
  void testGetTranslationUnitWithCompilationError();
  void testGetTranslationUnitWithDiagnostics();
  void testGetTranslationUnit();
};
