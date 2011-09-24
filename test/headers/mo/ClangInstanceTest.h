#include <cxxtest/TestSuite.h>
#include "mo/ClangInstance.h"

class ClangInstanceTest : public CxxTest::TestSuite { 
private:
  ClangInstance *_instance;
  
public:
  void setUp();
  void tearDown();
  void testHasNoDiagnostic();
  void testHasDiagnostics();
  void testHasNoWarning();
  void testHasWarnings();
  void testHasNoError();
  void testHasErrors();
  void testCodeCompilationFailException();
  void testReportDiagnostics();
  void testGetTranslationUnitWithCompilationError();
  void testGetTranslationUnitWithDiagnostics();
  void testGetTranslationUnit();
};
