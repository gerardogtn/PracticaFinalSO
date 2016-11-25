// Copyright 2016
#ifndef PROCESS_H
#define PROCESS_H

#include <ostream>
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

  virtual ~Process() {}

  bool operator==(const Process& other) const {
    return name == other.name &&
      priority == other.priority &&
      duration == other.duration &&
      arrivalTime == other.arrivalTime;
  }

  std::string getName() const { return name; }
  int getPriority() const { return priority; }
  double getDuration() const { return duration; }
  double getArrivalTime() const { return arrivalTime; }

  void reduceDuration(double difference) {
    duration -= difference;
  }

  friend std::ostream& operator<<(std::ostream& os, const Process& p);
};

#endif  // PROCESS_H
