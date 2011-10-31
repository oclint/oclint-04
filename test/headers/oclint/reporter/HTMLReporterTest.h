#include <cxxtest/TestSuite.h>
#include "oclint/reporter/HTMLReporter.h"

class HTMLReporterTest : public CxxTest::TestSuite { 
private:
  HTMLReporter *_reporter;
  
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
