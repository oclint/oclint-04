#include <cxxtest/TestSuite.h>
#include "oclint/reporter/PlainTextReporter.h"

class PlainTextReporterTest : public CxxTest::TestSuite { 
private:
  PlainTextReporter *_reporter;
  
public:
  void setUp();
  void tearDown();
  void testReportDiagnostics();
  void testReportEmptyDiagnostics();
  void testCursorLocationToPlainText();
  void testReportViolations();
  void testReportEmptyViolations();
};
