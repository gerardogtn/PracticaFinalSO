#ifndef GANTTCHARTHORIZONTAL_H
#define GANTTCHARTHORIZONTAL_H

#include <list>
#include <ostream>
#include <string>
#include "SchedulerStep.hpp"
#include "Process.hpp"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>


class GanttChartHorizontal {
private:
  std::list<SchedulerStep> steps;
  std::ostream& os;
public:
  GanttChartHorizontal(std::list<SchedulerStep> steps, std::ostream& os)
    : steps(steps), os(os) {}

  void write(){
    struct winsize w;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);

    double last = steps.back().getEndTime();
    int ndigits = 5;


    while(!steps.empty()){

        SchedulerStep current = steps.front();
        steps.pop_front();

        double s = current.getStartTime();
        double e = current.getEndTime();
        int ns = s/last*(w.ws_col-ndigits);
        int ne = e/last*(w.ws_col-ndigits);

        os << current.getName();
        for (int i = ndigits; i<ne; i++) {
            if(i>=ns){
                os << "=";
            }
            else{
                os << " ";
            }
        }
        os << std::endl;
        for(int i = 0;i<ndigits;i++){
            os << " ";
        }
        for (int i = ndigits; i<=ne; i++) {
            if(i==ne){
                os << e;
                std::list<Process> queue = current.getReadyQueue();
                while(!queue.empty()){
                    Process p = queue.front();
                    queue.pop_front();
                    os << " " << p.getName();
                }
            }
            else
                os << " ";
        }
        os << std::endl;
    }
  }

};

#endif
