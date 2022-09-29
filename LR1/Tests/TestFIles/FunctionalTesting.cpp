//
// Created by Vladimir Moshchuk on 27.09.22.
//
#include "gtest/gtest.h"
#include "postMachine.h"

class TestMachine : public ::testing::Test {
 protected:
  void SetUp() override {
   tape = new postMachine::tapeManager({'1','0','1'});
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

TEST_F(TestMachine, shiftRight) {
  ruller->push("->");
  int i =0;
  ruller->switcher(i);
  ASSERT_EQ("-^-",slide->output());
}

TEST_F(TestMachine, ShiftLeft){
  ruller->push("head_pos: 1");
  int i =0;
  ruller->switcher(i);
  ASSERT_EQ("-^-",slide->output());

  ruller->push("<-");
  ruller->switcher(i);
  ASSERT_EQ("^--",slide->output());
}

TEST_F(TestMachine, HeadPos){
  ruller->push("head_pos: 1");
  int i =0;
  ruller->switcher(i);
  ASSERT_EQ("-^-",slide->output());
}

TEST_F(TestMachine, deleteCellNumber){
  ruller->push("X");
  int i = 0;
  ruller->switcher(i);
  ASSERT_EQ("001",tape->output());
}
TEST_F(TestMachine, insertCellNumber){
  ruller->push("head_pos: 1");
  int i =0;
  ruller->switcher(i);
  ASSERT_EQ("-^-",slide->output());

  ruller->push("V");
  ruller->switcher(i);
  ASSERT_EQ("111",tape->output());
}

TEST_F(TestMachine, switcher){
  std::vector<std::string> commands = {"init_tape: (1,0,1)", "X", "? 1 0"};
  ruller->push(commands);
  int i = 2;
  ruller->switcher(i);
  ASSERT_EQ("001", tape->output());

  ruller->push("? 1 0");
  ruller->switcher(i);
  ASSERT_EQ("001101", tape->output());
}

TEST_F(TestMachine, history){
  std::vector<std::string> commands = {"init_tape: (1,0,1)", "X", "? 1 0"};

  ruller->push(commands);

  for (int i = 0; i < commands.size(); ++i) {
    EXPECT_EQ(commands[i], ruller->history()[i]);
  }
}

TEST_F(TestMachine, Stop){
  ruller->push("!");
  int i =0;
  ruller->switcher(i);
  EXPECT_EQ(true, ruller->stop());
}

TEST_F(TestMachine, InitTape){
  ruller->push("init_tape: (0,0,1)");
  int i =0;
  ruller->switcher(i);
  EXPECT_EQ("101001",tape->output());
}
int main(int argc, char *argv[]){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}