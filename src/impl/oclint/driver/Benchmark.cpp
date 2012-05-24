#include "oclint/driver/Benchmark.h"

void Benchmark::startConsumingArguments() {
  gettimeofday(&consumeArguments_start, NULL);
}

void Benchmark::finishConsumingArguments() {
  gettimeofday(&consumeArguments_end, NULL);
}

double Benchmark::consumeArguments() {
  return difftimeval(consumeArguments_end, consumeArguments_start);
}

void Benchmark::startLoadingRules() {
  gettimeofday(&loadRules_start, NULL);
}

void Benchmark::finishLoadingRules() {
  gettimeofday(&loadRules_end, NULL);
}

double Benchmark::loadRules() {
  return difftimeval(loadRules_end, loadRules_start);
}

void Benchmark::startParsingSourceCode() {
  gettimeofday(&clangInstance_start, NULL);
}

void Benchmark::finishParsingSourceCode() {
  gettimeofday(&clangInstance_end, NULL);
}

double Benchmark::clangInstance() {
  return difftimeval(clangInstance_end, clangInstance_start);
}

void Benchmark::startAnalyzingCode() {
  gettimeofday(&codeAnalysis_start, NULL);
}

void Benchmark::finishAnalyzingCode() {
  gettimeofday(&codeAnalysis_end, NULL);
}

double Benchmark::codeAnalysis() {
  return difftimeval(codeAnalysis_end, codeAnalysis_start);
}

void Benchmark::startRenderingReports() {
  gettimeofday(&renderReports_start, NULL);
}

void Benchmark::finishRenderingReports() {
  gettimeofday(&renderReports_end, NULL);
}

double Benchmark::renderReports() {
  return difftimeval(renderReports_end, renderReports_start);
}

double Benchmark::sum() {
  return consumeArguments() + loadRules() + clangInstance() + codeAnalysis() 
    + renderReports();
}

double Benchmark::difftimeval(timeval end, timeval start) {
  return end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
}


