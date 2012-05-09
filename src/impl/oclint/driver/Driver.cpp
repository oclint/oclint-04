#include "oclint/ClangInstance.h"
#include "oclint/SmellFinder.h"
#include "oclint/RuleSet.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/Version.h"
#include "oclint/exception/GenericException.h"
#include "oclint/reporter/PlainTextReporter.h"
#include "oclint/reporter/HTMLReporter.h"
#include "oclint/driver/CommandLineOptions.h"
#include "oclint/helper/DriverHelper.h"
#include "oclint/driver/Benchmark.h"
#include "oclint/driver/Driver.h"

static void versionPrinter() {
  cout << "OCLint (http://oclint.org/):" << endl
    << "  oclint version " << oclint_version() << endl
    << "  llvm version " << llvm_version() << endl;
}

static void parseCommandLineOptions(int argc, char* argv[]) {
  cl::SetVersionPrinter(versionPrinter);
  cl::ParseCommandLineOptions(argc, argv, 
    "OCLint, a static code analysis tool for Objective-C and related languages\n");
}

int Driver::main(int argc, char* argv[]) {
  _benchmark = new Benchmark();
  _benchmark->startConsumingArguments();
  parseCommandLineOptions(argc, argv);
  _benchmark->finishConsumingArguments();
  _executablePath = getExecutablePath(argv[0]);
  getCompilerArguments();
  if (consumeArgRulesPath() == 0 && RuleSet::numberOfRules() > 0) {
    try {
      ostream *out = outStream();
      int returnValue = execute(*out);
      disposeOutStream(out);
      dumpBenchmarks();
      return returnValue;
    }
    catch (GenericException& ex) {
      cerr << "Exception: " << ex.message << endl;
      return -3;
    }
  }
  else {
    cerr << "No rule found" << endl;
    return -2;
  }
  return -1;
}

void Driver::dumpBenchmarks() {
  cout << endl
    << "-------- Benchmark --------" << endl
    << "Consume Arguments: " << _benchmark->consumeArguments() << endl
    << "Load Rules: " << _benchmark->loadRules() << endl
    << "Clang Instance: " << _benchmark->clangInstance() << endl
    << "Code Analysis: " << _benchmark->codeAnalysis() << endl
    // << "Render Reports: " << _benchmark->renderReports() << endl
    << "Total: " << _benchmark->sum() << endl;
}

int Driver::dynamicLoadRules(string ruleDirPath) {
  DIR *dp = opendir(ruleDirPath.c_str());
  if (dp != NULL) {
    struct dirent *dirp;
    while ((dirp = readdir(dp))) {
      if (dirp->d_name[0] == '.') {
        continue;
      }
      string rulePath = ruleDirPath + "/" + string(dirp->d_name);
      if (dlopen(rulePath.c_str(), RTLD_NOW) == NULL) {
        cerr << dlerror() << endl;
        closedir(dp);
        return 3;
      }
    }
    closedir(dp);
  }
  return 0;
}

int Driver::consumeArgRulesPath() {
  if (argRulesPath.size() == 0) {
    loadRulesFromDefaultRulePath();
  }
  return loadRulesFromCustomRulePaths();
}

int Driver::loadRulesFromDefaultRulePath() {
  _benchmark->startLoadingRules();
  string defaultRulePath = _executablePath + "/../lib/oclint/rules";
  int errorCode = dynamicLoadRules(defaultRulePath);
  _benchmark->finishLoadingRules();
  return errorCode;
}

int Driver::loadRulesFromCustomRulePaths() {
  _benchmark->startLoadingRules();
  int returnFlag = 0;
  for (unsigned i = 0; i < argRulesPath.size() && returnFlag == 0; ++i) {
    returnFlag = dynamicLoadRules(argRulesPath[i]);
  }
  _benchmark->finishLoadingRules();
  return returnFlag;
}

void Driver::consumeOptArgument(string argKey, string argValue) {
  if (argValue != "-") {
    _compilerArguments.push_back("-" + argKey);
    _compilerArguments.push_back(argValue);
  }
}

void Driver::consumeListArgument(string argKey, vector<string> argValues) {
  for (unsigned i = 0; i < argValues.size(); ++i) {
    _compilerArguments.push_back("-" + argKey);
    _compilerArguments.push_back(argValues[i]);
  }
}

void Driver::consumeOptArguments() {
  consumeOptArgument("x", argLanguageType);
  consumeOptArgument("arch", argArch);
  consumeOptArgument("isysroot", argSysroot);
}

void Driver::consumeListArguments() {
  consumeListArgument("D", argMacros);
  consumeListArgument("F", argFrameworkSearchPath);
  consumeListArgument("include", argIncludes);
  consumeListArgument("I", argIncludeSearchPath);
}

void Driver::consumeRuleConfigurations() {
  for (unsigned i = 0; i < argRuleConfiguration.size(); ++i) {
    string configuration = argRuleConfiguration[i];
    int indexOfSeparator = configuration.find_last_of("=");
    string key = configuration.substr(0, indexOfSeparator);
    string value = configuration.substr(indexOfSeparator + 1, configuration.size() - indexOfSeparator - 1);
    RuleConfiguration::addConfiguration(key, value);
  }
}

void Driver::getCompilerArguments() {
  consumeOptArguments();
  consumeListArguments();
  cout << "BEGIN ARGUMENT" << endl;
  for (unsigned i = 0; i < _compilerArguments.size(); i++) {
    cout << _compilerArguments[i] << endl;
  }
  cout << "END ARGUMENT" << endl;
}

Reporter* Driver::reporter() {
  if (argReportType == html) {
    return new HTMLReporter();
  }
  return new PlainTextReporter();
}

int Driver::reportSmells(ClangInstance& instance, ostream& out) {
  int numberOfSmells = 0;
  if (instance.hasWarnings()) {
    out << instance.reportWarnings(*reporter());
    numberOfSmells += instance.warnings().size();
  }
  SmellFinder smellFinder;
  if (smellFinder.hasSmell(instance.getTranslationUnit())) {
    out << smellFinder.reportSmells(*reporter());
    numberOfSmells += smellFinder.numberOfViolations();
  }
  return numberOfSmells;
}

int Driver::executeFile(int argc, char** argv, ostream& out) {
  ClangInstance instance;
  _benchmark->startParsingSourceCode();
  instance.compileSourceFileToTranslationUnit(argv, argc);
  _benchmark->finishParsingSourceCode();
  if (instance.hasErrors()) {
    out << instance.reportErrors(*reporter());
    return instance.errors().size();
  }
  return reportSmells(instance, out);
}

int Driver::execute(ostream& out) {
  consumeRuleConfigurations();
  int totalNumberOfSmells = 0;
  out << reporter()->header();
  _benchmark->startAnalyzingCode();
  for (unsigned i = 0; i < argInputs.size(); i++) {
    char** argv = getArgv(_compilerArguments, argInputs[i]);
    totalNumberOfSmells += executeFile(_compilerArguments.size() + 1, argv, out);
  }
  _benchmark->finishAnalyzingCode();
  out << reporter()->footer();
  return totalNumberOfSmells;
}

ostream* Driver::outStream() {
  if (argOutput == "-") {
    return &cout;
  }
  ofstream *out = new ofstream(argOutput.c_str());
  if (!out->is_open()) {
    throw GenericException("Cannot open file " + argOutput);
  }
  return out;
}

void Driver::disposeOutStream(ostream* out) {
  if (out && argOutput != "-") {
    ofstream *fout = (ofstream *)out;
    fout->close();
  }
}

