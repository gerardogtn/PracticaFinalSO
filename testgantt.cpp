// Copyright 2016

#include <iostream>
#include <list>
#include "GanttChartWriter.hpp"
#include "RoundRobinScheduler.hpp"
#include "Process.hpp"

int main(int argc, char const *argv[]) {
  std::list<Process> processes { Process("Process1", 0.0, 20.0, 5),
      Process("Process2", 0.0, 5.0, 5)};
  RoundRobinScheduler scheduler(10, processes);
  GanttChartWriter writer(scheduler.getSteps(), std::cout);

  writer.write();
  return 0;
}
