// Copyright 2016
#ifndef SCHEDULERRESULT_H
#define SCHEDULERRESULT_H

class SchedulerResult {
 private:
  double averageWaitTime;
  double averageTurnAroundTime;

 public:
  SchedulerResult() {}
  virtual ~SchedulerResult() {}

  void setAverageWaitTime(double averageWaitTime) {
    this->averageWaitTime = averageWaitTime;
  }

  void setAverageTurnAroundTime(double averageTurnAroundTime) {
    this->averageTurnAroundTime = averageTurnAroundTime;
  }

  double getAverageWaitTime() const {
    return averageWaitTime;
  }

  double getAverageTurnAroundTime() const {
    return averageTurnAroundTime;
  }
};

#endif  // SCHEDULERRESULT_H
