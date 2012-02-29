#ifndef OCLINT_DRIVER_BENCHMARK_H
#define OCLINT_DRIVER_BENCHMARK_H

#include <ctime>

class Benchmark {
private:
  time_t consumeArguments_start;
  time_t consumeArguments_end;
  time_t loadRules_start;
  time_t loadRules_end;
  time_t clangInstance_start;
  time_t clangInstance_end;
  time_t codeAnalysis_start;
  time_t codeAnalysis_end;
  time_t renderReports_start;
  time_t renderReports_end;

public:
  void startConsumingArguments();
  void finishConsumingArguments();
  void startLoadingRules();
  void finishLoadingRules();
  void startParsingSourceCode();
  void finishParsingSourceCode();
  void startAnalyzingCode();
  void finishAnalyzingCode();
  void startRenderingReports();
  void finishRenderingReports();

public:
  double consumeArguments();
  double loadRules();
  double clangInstance();
  double codeAnalysis();
  double renderReports();
  double sum();
};

#endif
