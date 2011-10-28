#include <cxxtest/TestSuite.h>
#include "oclint/reporter/PlainTextReporter.h"

class PlainTextReporterTest : public CxxTest::TestSuite { 
private:
  PlainTextReporter *_reporter;
  
public:
  void setUp();
  void tearDown();
  void testHeader();
  void testFooter();
  void testReportDiagnostics();
  void testReportEmptyDiagnostics();
  void testReportViolations();
  void testReportEmptyViolations();
};
