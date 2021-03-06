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
  const int quanta;
  const int PROCESS_NUMBER;

  double currentTime;
  double waitingTime = 0.0;
  double turnaroundTime = 0.0;

  std::list<Process> processes;
  Process* last = nullptr;

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

  void onProcessNotReady(Process* next) {
    if (last == nullptr) {
      last = next;
      processes.push_back(*next);
    } else if (*last == *next) {
      currentTime = next->getArrivalTime();
      processes.push_front(*next);
      last = nullptr;
    }
  }

  void onBurstProcess(const Process& process) {
    updateClock(process.getDuration());
    turnaroundTime += currentTime - process.getArrivalTime();
  }

  void onReduceProcessDuration(Process* process) {
    updateClock(quanta);
    process->reduceDuration(quanta);
    processes.push_back(*process);
  }

  void updateClock(double time) {
    currentTime += time;
    updateWaitingTime(time);
  }

 public:
  explicit RoundRobinScheduler(int quanta, std::list<Process> processes)
    : quanta(quanta), PROCESS_NUMBER(processes.size()), processes(processes) {
      this->processes.sort(compareByArrivalTime);
      currentTime = this->processes.front().getArrivalTime();
    }
  virtual ~RoundRobinScheduler() {}

  std::list<SchedulerStep> getSteps() {
    std::list<SchedulerStep> steps = std::list<SchedulerStep>();

    while (!processes.empty()) {
      Process next = processes.front();
      processes.pop_front();
      double previousTime = currentTime;

      if (next.getArrivalTime() > currentTime) {
        onProcessNotReady(&next);
        continue;
      } else if (next.getDuration() <= quanta) {
        onBurstProcess(next);
      } else {
        onReduceProcessDuration(&next);
      }

      SchedulerStep step(next.getName(), previousTime,
                          currentTime, getReadyQueue());
      steps.push_back(step);
    }

    return steps;
  }

  double getAverageWaitTime() {
    return waitingTime / PROCESS_NUMBER;
  }

  double getAverageTurnAroundTime() {
    return turnaroundTime / PROCESS_NUMBER;
  }

  SchedulerResult getResult() {
    return SchedulerResult(getAverageWaitTime(), getAverageTurnAroundTime());
  }
};

#endif  // ROUNDROBINSCHEDULER_H
