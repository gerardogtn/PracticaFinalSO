
#ifndef FIXEDPRIORITYSCHEDULER_H
#define FIXEDPRIORITYSCHEDULER_H

#include <iostream>
#include <list>
#include <string>
#include <cctype>
// #include "SchedulerStep.hpp"
#include "Process.hpp"



class FixedPriorityScheduler{
private:
    double currentTime;
    std::list<Process> processes;

    static bool higherPriority( Process & a, Process & b){
        return a.getPriority() > b.getPriority();
    }
public:

    explicit FixedPriorityScheduler(std::list<Process> processes)
    : processes(processes) {
        currentTime = processes.front().getArrivalTime();
    }
    virtual ~FixedPriorityScheduler() {}

    void setSteps(){
        // std::list<SchedulerStep> steps = std::list<SchedulerStep>();

        Process currentProcess = processes.front();
        processes.pop_front();

        std::list<Process> queue;
        double t;
        Process next;
        bool finished = false;

        while (!finished) {
          queue.sort(higherPriority);
          if(!processes.empty()){
            next = processes.front();
            t = next.getArrivalTime()-currentTime;
            if(t>currentProcess.getDuration()){
              currentTime = currentTime + currentProcess.getDuration();
              currentProcess.reduceDuration(currentProcess.getDuration());
              currentProcess = queue.front();
              queue.pop_front();
            }
            else{
              currentProcess.reduceDuration(t);
              currentTime = next.getArrivalTime();
              processes.pop_front();
              // If smaller
              if(t<currentProcess.getDuration()){
                if(higherPriority(next,currentProcess)){
                  queue.push_back(currentProcess);
                  currentProcess = next;
                }
                else
                  queue.push_back(next);
              }
              // If equal
              else{
                currentProcess = queue.front();
                queue.pop_front();
              }

            }
          }
          else{
            next = queue.front();
            currentTime = currentTime + currentProcess.getDuration();
            currentProcess.reduceDuration(currentProcess.getDuration());
            if(!queue.empty()){
                currentProcess = queue.front();
                queue.pop_front();
            }
            else
                finished = true;
          }

        }

    }

};

#endif
