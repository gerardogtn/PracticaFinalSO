// Copyright 2016
#ifndef PROCESSREADER_H
#define PROCESSREADER_H

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <utility>
#include "Process.hpp"

class ProcessReader {
 private:
  std::ifstream file;
  std::string name;
  double arrivalTime;
  double duration;
  int priority;

  int getQuanta() {
    int result;
    file >> result;
    if (result <= 0)
      throw std::runtime_error("Quanta must be bigger than zero");
    return result;
  }

  std::list<Process> getProcesses() {
    std::list<Process> out;

    while (file >> name >> arrivalTime >> duration >> priority) {
      out.push_back(Process(name, arrivalTime, duration, priority));
    }

    return out;
  }

 public:
  explicit ProcessReader(std::string fileName) {
    file.open(fileName);
  }

  virtual ~ProcessReader() {
    file.close();
  }

  std::pair<int, std::list<Process>> read() {
    return make_pair(getQuanta(), getProcesses());
  }
};

#endif  // PROCESSREADER_H
