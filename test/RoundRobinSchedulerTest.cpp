// Copyright 2016

#include <list>
#include "gmock/gmock.h"
#include "../Process.hpp"
#include "../RoundRobinScheduler.hpp"
#include "../SchedulerStep.hpp"

using namespace testing;

TEST(ARoundRobinScheduler, SingleProcessWithZeroArrivalTime) {
  std::list<Process> processes { Process("Process1", 0.0, 10.0, 5) };
  RoundRobinScheduler scheduler(5, processes);

  std::list<SchedulerStep> steps { SchedulerStep("Process1", 0.0, 5.0),
    SchedulerStep("Process1", 5.0, 10.0) };

  ASSERT_THAT(scheduler.getSteps(), Eq(steps));
}

TEST(ARoundRobinScheduler, SingleProcessWithNotZeroArrivalTime) {
  std::list<Process> processes { Process("Process1", 2.5, 10.0, 5) };
  RoundRobinScheduler scheduler(5, processes);

  std::list<SchedulerStep> steps { SchedulerStep("Process1", 2.5, 7.5),
    SchedulerStep("Process1", 7.5, 12.5) };

  ASSERT_THAT(scheduler.getSteps(), Eq(steps));
}

TEST(ARoundRobinScheduler, MultipleProcessWithZeroArrivalTime) {
  std::list<Process> processes { Process("Process1", 0.0, 10.0, 5),
      Process("Process2", 0.0, 5.0, 5)};
  RoundRobinScheduler scheduler(5, processes);

  std::list<SchedulerStep> steps { SchedulerStep("Process1", 0.0, 5.0),
    SchedulerStep("Process2", 5.0, 10.0),
    SchedulerStep("Process1", 10.0, 15.0)};

  ASSERT_THAT(scheduler.getSteps(), Eq(steps));
}

TEST(ARoundRobinScheduler, MultipleProcessWithNonZeroArrivalTime) {
  std::list<Process> processes { Process("Process1", 2.5, 10.0, 5),
      Process("Process2", 2.5, 5.0, 5)};
  RoundRobinScheduler scheduler(5, processes);

  std::list<SchedulerStep> steps { SchedulerStep("Process1", 2.5, 7.5),
    SchedulerStep("Process2", 7.5, 12.5),
    SchedulerStep("Process1", 12.5, 17.5)};

  ASSERT_THAT(scheduler.getSteps(), Eq(steps));
}

TEST(ARoundRobinScheduler, UnsortedMultipleProcessWithNonZeroArrivalTime) {
  std::list<Process> processes { Process("Process1", 2.5, 10.0, 5),
      Process("Process2", 0, 5.0, 5)};
  RoundRobinScheduler scheduler(5, processes);

  std::list<SchedulerStep> steps { SchedulerStep("Process2", 0.0, 5.0),
    SchedulerStep("Process1", 5.0, 10.0),
    SchedulerStep("Process1", 10.0, 15.0)};

  ASSERT_THAT(scheduler.getSteps(), Eq(steps));
}

TEST(ARoundRobinScheduler, MultipleProcessesWithTimeDifferenceLargerThanQuanta) {
  std::list<Process> processes { Process("Process1", 0, 5.0, 5),
      Process("Process2", 15.0, 5.0, 5)};
  RoundRobinScheduler scheduler(5, processes);

  std::list<SchedulerStep> steps { SchedulerStep("Process1", 0.0, 5.0),
    SchedulerStep("Process2", 15.0, 20.0)};

  ASSERT_THAT(scheduler.getSteps(), Eq(steps));
}
