#include <cxxtest/TestSuite.h>
#include "mo/reporter/PlainTextReporter.h"

class PlainTextReporterTest : public CxxTest::TestSuite { 
private:
  PlainTextReporter *reporter;
  
public:
  void setUp();
  void tearDown();
  void testReportDiagnostics();
};
