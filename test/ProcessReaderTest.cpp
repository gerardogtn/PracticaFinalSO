// Copyright 2016

#include <exception>
#include <list>
#include <utility>
#include "gmock/gmock.h"
#include "../Process.hpp"
#include "../ProcessReader.hpp"

using namespace testing;

class ASampleInputProcessReader : public Test {
 public:
  ProcessReader processReader;
  std::pair<int, std::list<Process>> out;
  ASampleInputProcessReader() : processReader("../sampleInput") {
    out = processReader.read();
  }
};

TEST_F(ASampleInputProcessReader, ParsesQuanta) {
  ASSERT_THAT(out.first, Eq(8));
}

TEST_F(ASampleInputProcessReader, ParsesProcess) {
  std::list<Process> processes;
  processes.push_back(Process("Proc1", 0.0, 14.0, 5));
  processes.push_back(Process("Proc2", 2.5,  3.5, 2));

  ASSERT_THAT(out.second, Eq(processes));
}


TEST(AnInvalidQuantaProcessReader, FailsOnLessThanZeroQuanta) {
  ProcessReader processReader("../invalidQuanta");

  ASSERT_ANY_THROW(processReader.read());
}
