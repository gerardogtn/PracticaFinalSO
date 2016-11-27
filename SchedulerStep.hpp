// Copyright 2016
#ifndef SCHEDULERSTEP_H
#define SCHEDULERSTEP_H

#include <iostream>
#include <list>
#include <string>
#include "Process.hpp"

class SchedulerStep {
 private:
  std::string name;
  std::list<Process> readyQueue;
  double startTime;
  double endTime;

 public:
  SchedulerStep(std::string name, double startTime, double endTime,
    std::list<Process> readyQueue) : name(name), startTime(startTime)
    , endTime(endTime), readyQueue(readyQueue) {}
  ~SchedulerStep() {}

  std::string getName() { return name; }
  double getStartTime() { return startTime; }
  double getEndTime() { return endTime; }
  double getDuration() { return endTime - startTime; }
  std::list<Process> getReadyQueue() { return readyQueue; }

  bool operator==(const SchedulerStep& other) const {
    return name == other.name &&
      startTime == other.startTime &&
      endTime == other.endTime;
  }

  friend std::ostream& operator<<(std::ostream& os, const SchedulerStep& step);
};

std::ostream& operator<<(std::ostream& os, const SchedulerStep& step) {
  os << step.name << " " << step.startTime << " " << step.endTime;
  return os;
}

#endif  // SCHEDULERSTEP_H
