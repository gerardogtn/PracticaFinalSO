// Copyright 2016
#include "Process.hpp"

std::ostream& operator<<(std::ostream& os, const Process& p) {
  os << " { name: " << p.name;
  os << " arrival: " << p.arrivalTime << ", ";
  os << " duration: " << p.duration << ", ";
  os << " priority: " << p.priority << ", ";
  os << " }";
  return os;
}
