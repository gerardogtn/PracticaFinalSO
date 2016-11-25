// Copyright 2016
#ifndef ROUNDROBINSCHEDULER_H
#define ROUNDROBINSCHEDULER_H

#include <iostream>
#include <list>
#include "processComparison.hpp"
#include "SchedulerStep.hpp"
#include "Process.hpp"

class RoundRobinScheduler {
 private:
  double currentTime;
  int quanta;
  std::list<Process> processes;

 public:
  explicit RoundRobinScheduler(int quanta, std::list<Process> processes)
    : quanta(quanta), processes(processes) {
      this->processes.sort(compareByArrivalTime);
      currentTime = this->processes.front().getArrivalTime();
    }
  virtual ~RoundRobinScheduler() {}

  std::list<SchedulerStep> getSteps() {
    std::list<SchedulerStep> steps = std::list<SchedulerStep>();

    while (!processes.empty()) {
      Process next = processes.front();
      processes.pop_front();

      double nextTime;
      if (next.getDuration() <= quanta) {
        nextTime = currentTime + next.getDuration();
      } else {
        nextTime = currentTime + quanta;
        next.reduceDuration(quanta);
        processes.push_back(next);
      }

      steps.push_back(SchedulerStep(next.getName(), currentTime, nextTime));
      currentTime = nextTime;
    }

    return steps;
  }
};

#endif  // ROUNDROBINSCHEDULER_H
