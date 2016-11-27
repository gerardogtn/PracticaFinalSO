
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
        std::list<Process> queue;

        Process currentProcess = processes.front();
        processes.pop_front();
        queue.push_back(currentProcess);
        Process next;


        double t;
        while (!queue.empty()) {
            queue.sort(higherPriority);
            currentProcess = queue.front();
            queue.pop_front();

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
                    if(t!=currentProcess.getDuration()){
                        queue.push_back(currentProcess);
                    }
                    queue.push_back(next);
                }
            }
            else{
                next = queue.front();
                currentTime = currentTime + currentProcess.getDuration();
                currentProcess.reduceDuration(currentProcess.getDuration());
            }

        }

    }

};

#endif
