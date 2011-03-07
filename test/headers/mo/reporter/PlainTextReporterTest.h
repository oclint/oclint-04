#include <cxxtest/TestSuite.h>
#include "mo/reporter/PlainTextReporter.h"

class PlainTextReporterTest : public CxxTest::TestSuite { 
private:
  PlainTextReporter *_reporter;
  
public:
  void setUp();
  void tearDown();
  void testReportDiagnostics();
  void testCursorLocationToPlainText();
  void testReportViolations();
};
