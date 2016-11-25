// Copyright 2016
#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
 private:
  std::string name;
  int priority;
  int duration;

 public:
  Process(std::string name, int priority, int duration) :
    name(name), priority(priority), duration(duration) {}

  virtual ~Process() {}
};

#endif  // PROCESS_H
