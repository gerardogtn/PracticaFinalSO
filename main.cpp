// Copyright 2016
#include <list>
#include <thread>
#include <string>
#include "Process.hpp"
#include "ProcessReader.hpp"
#include "SchedulerResult.hpp"
#include "SocketProcessSender.hpp"

void fixedPriorityScheduler(std::list<Process> processes, int quanta,
  SchedulerResult* schedulerResult);
void roundRobinPriorityScheduler(std::list<Process> processes, int quanta,
  SchedulerResult* schedulerResult);

int main(int argc, char const *argv[]) {
  SchedulerResult fixedPriorityResult;
  SchedulerResult roundRobinResult;

  ProcessReader reader;
  auto pair = reader.read(arv[1]);
  std::list<Process> processes = pair.second;

  std::thread fixedPriorityThread(fixedPriorityScheduler, pair.first, processes,
    std::ref(fixedPriorityResult));
  std::thread roundRobinThread(roundRobinPriorityScheduler, pair.first,
    processes, std::ref(roundRobinResult));

  fixedPriorityThread.join();
  roundRobinThread.join();

  SocketProcessSender socketSender;
  socketSender.send("fixed priority", fixedPriorityResult);
  socketSender.send("round robin", roundRobinResult);

  return 0;
}

void fixedPriorityScheduler(std::list<Process> processes, int quanta,
  SchedulerResult* schedulerResult) {
}

void roundRobinPriorityScheduler(std::list<Process> processes, int quanta,
  SchedulerResult* schedulerResult) {
}
