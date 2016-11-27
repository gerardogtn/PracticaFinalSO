// Copyright 2016
#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
 private:
  std::string name;
  int priority;
  double duration;
  double arrivalTime;

 public:
  Process(std::string name, double arrivalTime, double duration, int priority) :
    name(name), priority(priority), duration(duration),
    arrivalTime(arrivalTime) {}

  Process(){}
  
  virtual ~Process() {}

  bool operator==(const Process& other) const {
    return name == other.name &&
      priority == other.priority &&
      duration == other.duration &&
      arrivalTime == other.arrivalTime;
  }

  std::string getName() { return name; }
  int getPriority() { return priority; }
  double getDuration() { return duration; }
  double getArrivalTime() { return arrivalTime; }

  void reduceDuration(double difference) {
    duration -= difference;
  }
};

#endif  // PROCESS_H
