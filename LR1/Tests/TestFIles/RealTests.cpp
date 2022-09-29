//
// Created by Vladimir Moshchuk on 28.09.22.
//
#include "gtest/gtest.h"
#include "postMachine.h"

class RealTestMachine : public ::testing::Test {
 protected:
  void SetUp() override {
    tape = new postMachine::tapeManager({});
    slide = new postMachine::slide(*tape);
    ruller = new postMachine::ruller(*slide, *tape);
  }
  void TearDown() override {
    delete tape;
    delete slide;
    delete ruller;
  }
  postMachine::tapeManager *tape{};
  postMachine::slide *slide{};
  postMachine::ruller *ruller{};
};

TEST_F(RealTestMachine, RealTestNumber1){
  std::vector<std::string> commands = {
      "init_tape: (1,0,1,0,0,1,1)",
      "head_pos: 6",
      "<-",
      "? 2 4",
      "V",
      "->",
      "X",
      "head_pos: 1",
      "->",
      "X",
      "!"
  };

  ruller->push(commands);

  int index = 0;
  while (true) {
    ruller->switcher(index);
    if(ruller->stop()){
      break;
    }
  }
  EXPECT_EQ("1000101", tape->output());
}

TEST_F(RealTestMachine, RealTestNumber2){
std::vector<std::string> commands = {
    "init_tape: (1,0,1,0,0,1,1)",
    "head_pos: 3",
    "<-",
    "? 4 2",
    "X",
    "->",
    "? 7 5",
    "X",
    "->",
    "? 2 10",
    "!"
};

ruller->push(commands);
int index = 0;
while (true) {
ruller->switcher(index);


if(ruller->stop()){
break;
}
}
EXPECT_EQ("0000000", tape->output());
}

TEST_F(RealTestMachine, RealTestNumber3){
  std::vector<std::string> commands = {
      "init_tape: (0,1,0,1,0,1,1,0)",
      "head_pos: 3",
      "<-",
      "? 4 2",
      "X",
      "->",
      "? 7 5",
      "X",
      "->",
      "? 2 10",
      "V",
      "!"
  };

  ruller->push(commands);
  int index = 0;
  while (true) {
    ruller->switcher(index);

    if(ruller->stop()){
      break;
    }
  }
  EXPECT_EQ("00001110", tape->output());
}