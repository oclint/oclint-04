#include "oclint/reporter/HTMLReporter.h"

#include "oclint/helper/CursorHelper.h"
#include "oclint/Violation.h"
#include "oclint/Rule.h"
#include "oclint/Version.h"

const string HTMLReporter::header() const {
  return "<html>\n<head>\n<title>OCLint Report</title>\n</head>\n<body>\n\
    <h1>OCLint Report</h1>\n<ul>\n<table><tr><td>Rule Name</td>\
    <td>File Name</td><td>Line</td><td>Column</td><td>Description</td></tr>";
}

const string HTMLReporter::footer() const {
  return "</table></ul>\n<p><a href=\"http://oclint.org\">OCLint</a> v" 
    + oclint_version() + "</p>\n</body>\n</html>\n";
}

const string HTMLReporter::reportDiagnostics(
  const vector<CXDiagnostic>& diagnostics) const {
  return ""; 
  //"<li>Sorry, html output is not supported in this version, 
  //please check out previous or next version.</li>\n";
}

const string HTMLReporter::reportViolations(
  const vector<Violation>& violations) const {
  string formatedViolations;
  for (int index = 0, numberOfViolations = violations.size(); 
    index < numberOfViolations; 
    index++) {
    Violation violation = violations.at(index);
    formatedViolations += "<tr><td>" + violation.rule->name() + "</td>";
    formatedViolations += "<td>" 
      + CursorHelper::getFileName(violation.cursor) + "</td>";
    formatedViolations += "<td>" 
      + CursorHelper::getLineNumber((violation.cursor)) + "</td>";
    formatedViolations += "<td>" 
      + CursorHelper::getColumnNumber(violation.cursor) + "</td>";
    formatedViolations += "<td>" + violation.description + "</td></tr>\n";
  }
  return formatedViolations;
}
