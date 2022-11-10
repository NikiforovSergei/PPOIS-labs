//
// Created by Vladimir Moshchuk on 28.09.22.
//
#include "gtest/gtest.h"
#include "../../stc/Tree/Tree.h"
#include "../../stc/Parser/parser.h"

class RealTestMachine : public ::testing::Test {
 protected:
  void SetUp() override {
    stc::SavedSet set;
  }
};

TEST_F(RealTestMachine, RealTestNumber1){
  std::string output;
  stc::Tree::print(stc::Parser::solution("{a,b,c} + {b,c,k}"), output);
  EXPECT_EQ("{a, b, c, k}", output);
}

TEST_F(RealTestMachine, RealTestNumber2){
  std::string output;
  stc::Tree::print(stc::Parser::solution("{a,{{b, k,f}, {e,m}},c} + {b,c,k}"), output);
  EXPECT_EQ("{a, c, b, k, {{b, k, f}, {e, m}}}", output);
}

TEST_F(RealTestMachine, RealTestNumber3){
  std::string output;
  stc::Tree::print(stc::Parser::solution("{a,b,c} * {a,b,d}"), output);
  EXPECT_EQ("{a, b}", output);
}
TEST_F(RealTestMachine, RealTestNumber4){
  std::string output;
  stc::Tree::print(stc::Parser::solution("B = A = {a, b, c}"), output);
  EXPECT_EQ("{a, b, c}", output);
}
TEST_F(RealTestMachine, RealTestNumber5){
  std::string output;
  stc::Tree::print(stc::Parser::solution("{a}+{}*(({}+{a,{a,b}}))"), output);
  EXPECT_EQ("{a}", output);
}
TEST_F(RealTestMachine, RealTestNumber5){
  std::string output;
  stc::Tree::print(stc::Parser::solution("{a}+{}*(({}+{a,{a,b}}))"), output);
  EXPECT_EQ("{a}", output);
}