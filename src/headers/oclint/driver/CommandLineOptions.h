#include <string>
#include <llvm/Support/CommandLine.h>

using namespace std;
using namespace llvm;
using namespace cl;

/* ----------------
   input and output
   ---------------- */

list<string> argInputs(Positional, desc("<input files>"), OneOrMore);
//opt<string> argXCodeProject("xcode", desc("Specify the XCode project to inspect on"), value_desc("xcode project or workspace"), init("-"));
opt<string> argOutput("o", desc("Write output to <file>"), value_desc("file"), init("-"));

enum ReportType {
  text, html
};
opt<ReportType> argReportType(desc("Choose report type:"), values(
  clEnumVal(text , "Plain text report"),
  clEnumVal(html, "HTML formatted report"),
clEnumValEnd));

/* ----------------------
   compiler configuration
   ---------------------- */

list<string> argIncludeSearchPath("I", Prefix, desc("Add directory to include search path"), value_desc("directory"), ZeroOrMore);
list<string> argFrameworkSearchPath("F", Prefix, desc("Add directory to framework include search path"), value_desc("directory"), ZeroOrMore);
list<string> argMacros("D", Prefix, desc("Predefine the specified macro"), value_desc("macro"), ZeroOrMore);
opt<string> argSysroot("isysroot", desc("Add directory to SYSTEM include search path"), value_desc("directory"), init("-"));
list<string> argIncludes("include", desc("Include file before parsing"), value_desc("file"), ZeroOrMore);
opt<string> argLanguageType("x", desc("Input language type"), value_desc("value"), init("-"));
opt<string> argArch("arch", desc("Specify which architecture (e.g. ppc, i386, x86_64, armv7) the compilation should targets."), value_desc("arch_name"), init("-"));

/* --------------------
   oclint configuration
   -------------------- */

list<string> argRulesPath("R", Prefix, desc("Add directory to rule loading path"), value_desc("directory"), ZeroOrMore);
list<string> argRuleConfiguration("rc", desc("Change the baheviour of rules"), value_desc("paramemter>=<value"), ZeroOrMore);

