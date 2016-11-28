// Copyright 2016
#include <fstream>
#include <iostream>
#include <list>
#include <thread>
#include <string>
#include "FixedPriorityScheduler.hpp"
#include "GantChartHorizontal.hpp"
#include "GanttChartWriter.hpp"
#include "Process.hpp"
#include "ProcessReader.hpp"
#include "SchedulerResult.hpp"
#include "SchedulerStep.hpp"
#include "SocketProcessSender.hpp"
#include "RoundRobinScheduler.hpp"

void fixedPriorityScheduler(std::list<Process> processes, std::string fileName,
  SocketProcessSender socketSender);
void roundRobinPriorityScheduler(std::list<Process> processes, int quanta,
  std::string fileName, SocketProcessSender socketSender);

void checkInput(int numberOfArguments) {
  if (numberOfArguments < 3) {
    std::cout << "Error de uso: especificar nombre de archivo de entrada y numero de puerto de socket" << '\n';
    std::cout << "Ejemplo: " << "./main.o procesos.txt 8000" << '\n';
    exit(-1);
  }
}

int main(int argc, char const *argv[]) {
  checkInput(argc);

  ProcessReader reader(argv[1]);
  auto pair = reader.read();
  std::list<Process> processes = pair.second;

  SocketProcessSender socketSender(atoi(argv[2]));
  std::thread fixedPriorityThread(fixedPriorityScheduler, processes, argv[1],
    socketSender);
  std::thread roundRobinThread(roundRobinPriorityScheduler, processes,
    pair.first, argv[1], socketSender);

  fixedPriorityThread.join();
  roundRobinThread.join();

  return 0;
}

void fixedPriorityScheduler(std::list<Process> processes, std::string fileName,
  SocketProcessSender socketSender) {
  std::ofstream out;
  out.open(fileName + "_FixedPriority");

  FixedPriorityScheduler scheduler(processes);
  std::cout << "Obteniendo steps" << '\n';
  std::list<SchedulerStep> steps = scheduler.getSteps();
  std::cout << "Listo" << '\n';


  GanttChartWriter writer(steps, out);
  writer.write();

  out << "\n \n Gantt Chart horizontal: \n";
  GanttChartHorizontal horizontal(steps, out);
  horizontal.write();

  out.close();
}

void roundRobinPriorityScheduler(std::list<Process> processes, int quanta,
  std::string fileName, SocketProcessSender socketSender) {
  std::ofstream out;
  out.open(fileName + "_RoundRobin");

  RoundRobinScheduler scheduler(quanta, processes);
  std::list<SchedulerStep> steps = scheduler.getSteps();

  GanttChartWriter writer(steps, out);
  writer.write();

  out << "\n \n Gantt Chart horizontal: \n";
  GanttChartHorizontal horizontal(steps, out);
  horizontal.write();

  socketSender.send("Round robin: ", scheduler.getResult());
  out.close();
}
