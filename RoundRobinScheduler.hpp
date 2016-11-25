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
  Process* last = nullptr;
  double waitingTime;
  int processNum;

 public:
  explicit RoundRobinScheduler(int quanta, std::list<Process> processes)
    : quanta(quanta), processes(processes) {
      this->processes.sort(compareByArrivalTime);
      currentTime = this->processes.front().getArrivalTime();
      processNum = processes.size();
    }
  virtual ~RoundRobinScheduler() {}

  std::list<SchedulerStep> getSteps() {
    std::list<SchedulerStep> steps = std::list<SchedulerStep>();

    while (!processes.empty()) {
      Process next = processes.front();
      processes.pop_front();

      double nextTime;
      if (next.getArrivalTime() > currentTime) {
        if (last == nullptr) {
          last = &next;
        } else if (*last == next) {
          currentTime += quanta;
        }
        processes.push_back(next);
        continue;
      }
      if (next.getDuration() <= quanta) {
        nextTime = currentTime + next.getDuration();
        waitingTime += next.getDuration() * processes.size();
      } else {
        nextTime = currentTime + quanta;
        next.reduceDuration(quanta);
        processes.push_back(next);
        waitingTime += next.getDuration() * processes.size();
      }

      last = nullptr;
      steps.push_back(SchedulerStep(next.getName(), currentTime, nextTime));
      currentTime = nextTime;
    }

    return steps;
  }

  double getAverageWaitTime() {
    return waitingTime / processNum;
  }
};

#endif  // ROUNDROBINSCHEDULER_H
