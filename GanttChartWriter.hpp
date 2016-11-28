// Copyright 2016
#ifndef GANTTCHARTWRITER_H
#define GANTTCHARTWRITER_H

#include <list>
#include <ostream>
#include <string>
#include "SchedulerStep.hpp"
#include "Process.hpp"

class GanttChartWriter {
 private:
  std::list<SchedulerStep> steps;
  std::ostream& os;
  int minSpace;

  void write(const std::list<Process>& queue) {
    os << "Ready queue (in order): ";
    for (Process p : queue) {
      os << p.getName() << " ";
    }
    os << '\n';
  }

  void writeInBetweenPipes(std::string s, char delimiter) {
    os << "|" << s << "|" << delimiter;
  }

  void writePipes(SchedulerStep step, int length) {
    int iterations = step.getDuration() / minSpace;
    iterations = iterations - 1;
    std::string blank(length, ' ');
    for (int i = 0; i < iterations; i++) {
      writeInBetweenPipes(blank, '\n');
    }
  }

  void write(SchedulerStep step) {
    int length = step.getName().size() + 2;
    std::string underscores(length, '_');
    os << underscores << step.getStartTime() << "\n";
    writeInBetweenPipes(step.getName(), ' ');
    write(step.getReadyQueue());
    writePipes(step, length - 2);
    os << underscores << step.getEndTime() << "\n";
  }

 public:
  explicit GanttChartWriter(std::list<SchedulerStep> steps,
    std::ostream& os) : steps(steps), os(os) {
      minSpace = steps.front().getDuration();
      for (auto step : steps) {
        if (minSpace > step.getDuration()) minSpace = step.getDuration();
      }
      if (minSpace == 0) minSpace = 1;
    }

  void write() {
    for (SchedulerStep s : steps) {
      write(s);
    }
  }
};

#endif  // GANTTCHARTWRITER_H
