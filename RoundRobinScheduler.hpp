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
  double waitingTime = 0.0;
  double turnaroundTime = 0.0;
  int processNum;

  std::list<Process> getReadyQueue() {
    std::list<Process> readyQueue;
    for (Process p : processes) {
      if (p.getArrivalTime() <= currentTime) {
        readyQueue.push_back(p);
      }
    }
    return readyQueue;
  }

  void updateWaitingTime(double wait) {
    std::list<Process> readyQueue = getReadyQueue();
    waitingTime += readyQueue.size() * wait;
  }

  void onProcessNotReady(Process* next, double * currentTime) {
    if (last == nullptr) {
      last = next;
    } else if (*last == *next) {
      *currentTime = next->getArrivalTime();
      last = nullptr;
    }
    processes.push_back(*next);
  }

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
        onProcessNotReady(&next, &currentTime);
        continue;
      }
      if (next.getDuration() <= quanta) {
        nextTime = currentTime + next.getDuration();
        updateWaitingTime(next.getDuration());
        turnaroundTime += nextTime - next.getArrivalTime();
      } else {
        nextTime = currentTime + quanta;
        next.reduceDuration(quanta);
        updateWaitingTime(quanta);
        processes.push_back(next);
      }

      steps.push_back(SchedulerStep(next.getName(), currentTime, nextTime));
      currentTime = nextTime;
    }

    return steps;
  }

  double getAverageWaitTime() {
    return waitingTime / processNum;
  }

  double getAverageTurnAroundTime() {
    return turnaroundTime / processNum;
  }
};

#endif  // ROUNDROBINSCHEDULER_H
