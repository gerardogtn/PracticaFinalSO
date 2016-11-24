// Copyright 2016

#include <cstdlib>
#include "SchedulerResult.hpp"
#include "SocketProcessSender.hpp"

int main(int argc, char const *argv[]) {
  SchedulerResult result;
  result.setAverageWaitTime(1.5);
  result.setAverageTurnAroundTime(2.5);

  SocketProcessSender socketsender(atoi(argv[1]));
  socketsender.send("test", result);

  result.setAverageWaitTime(3.5);
  result.setAverageTurnAroundTime(5.0);
  socketsender.send("other", result);
  return 0;
}
