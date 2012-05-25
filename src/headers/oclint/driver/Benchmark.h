#ifndef OCLINT_DRIVER_BENCHMARK_H
#define OCLINT_DRIVER_BENCHMARK_H

#include <sys/time.h>

class Benchmark
{
private:
  timeval consumeArguments_start;
  timeval consumeArguments_end;
  timeval loadRules_start;
  timeval loadRules_end;
  timeval clangInstance_start;
  timeval clangInstance_end;
  timeval codeAnalysis_start;
  timeval codeAnalysis_end;
  timeval renderReports_start;
  timeval renderReports_end;

  double difftimeval(timeval end, timeval start);

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
