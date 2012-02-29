#include "oclint/driver/Benchmark.h"

void Benchmark::startConsumingArguments() {
  time(&consumeArguments_start);
}

void Benchmark::finishConsumingArguments() {
  time(&consumeArguments_end);
}

double Benchmark::consumeArguments() {
  return difftime(consumeArguments_end, consumeArguments_start);
}

void Benchmark::startLoadingRules() {
  time(&loadRules_start);
}

void Benchmark::finishLoadingRules() {
  time(&loadRules_end);
}

double Benchmark::loadRules() {
  return difftime(loadRules_end, loadRules_start);
}

void Benchmark::startParsingSourceCode() {
  time(&clangInstance_start);
}

void Benchmark::finishParsingSourceCode() {
  time(&clangInstance_end);
}

double Benchmark::clangInstance() {
  return difftime(clangInstance_end, clangInstance_start);
}

void Benchmark::startAnalyzingCode() {
  time(&codeAnalysis_start);
}

void Benchmark::finishAnalyzingCode() {
  time(&codeAnalysis_end);
}

double Benchmark::codeAnalysis() {
  return difftime(codeAnalysis_end, codeAnalysis_start);
}

void Benchmark::startRenderingReports() {
  time(&renderReports_start);
}

void Benchmark::finishRenderingReports() {
  time(&renderReports_end);
}

double Benchmark::renderReports() {
  return difftime(renderReports_end, renderReports_start);
}

double Benchmark::sum() {
  return consumeArguments() + loadRules() + clangInstance() + codeAnalysis() + renderReports();
}

