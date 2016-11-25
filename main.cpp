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

// Para compilar: g++ main.cpp -o main.o -std=c++11 -pthread
// Para correr: ./main.o nombreArchivo numPuerto
//          Ej: ./main.o procesos 12800
int main(int argc, char const *argv[]) {
  SchedulerResult fixedPriorityResult;
  SchedulerResult roundRobinResult;

  ProcessReader reader(argv[1]);
  auto pair = reader.read();
  std::list<Process> processes = pair.second;

  std::thread fixedPriorityThread(fixedPriorityScheduler, pair.first, processes,
    std::ref(fixedPriorityResult));
  std::thread roundRobinThread(roundRobinPriorityScheduler, pair.first,
    processes, std::ref(roundRobinResult));

  fixedPriorityThread.join();
  roundRobinThread.join();

  SocketProcessSender socketSender(atoi(argv[2]));
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
