// Copyright 2016
#ifndef PROCESSCOMPARISON_H
#define PROCESSCOMPARISON_H

#include "Process.hpp"

bool compareByArrivalTime(const Process& first, const Process& second) {
  return first.getArrivalTime() < second.getArrivalTime();
}

#endif  // PROCESSCOMPARISON_H
