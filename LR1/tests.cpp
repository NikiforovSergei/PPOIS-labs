#include "patterns.cpp"
#include "machine.cpp"
#include <gtest/gtest.h>
#include "fstream"

TEST(TestConstructor, TestPatternsConstructor_1){
    ASSERT_NO_THROW(patterns p);
}
TEST(TestConstructor, TestPatternsConstructor_2){
    ASSERT_NO_THROW(patterns p = patterns("+a->b+;+b->a+;+->|;->+"));
}

TEST(TestConstructor, TestMachineConstructor_1){
    ASSERT_NO_THROW(machine m);
}
TEST(TestConstructor, TestMachineConstructor_2){
    ASSERT_NO_THROW(machine m = machine("aaaabbbb", "a->b;b->a"));
}
TEST(TestConstructor, TestMachineConstructor_3){
    patterns rules = patterns("a->b;b->a");
    ASSERT_NO_THROW(machine m = machine("aaabbb", rules));
}


TEST(TestEqualUnequal, TestEqualPatterns_1) {
    patterns test_1 = patterns("+a->b+;+b->a+"), test_2 = patterns("+a->b+;+b->a+");

    ASSERT_TRUE(test_1 == test_2);
}
TEST(TestEqualUnequal, TestEqualPatterns_2) {
    patterns test_1 = patterns("+a->b+;+b->a+"), test_2 = patterns("+a->b+");

    ASSERT_FALSE(test_1 == test_2);
}
TEST(TestEqualUnequal, TestEqualPatterns_3) {
    patterns test_1 = patterns("+a->b+;+b->a+"), test_2;

    ASSERT_FALSE(test_1 == test_2);
}

TEST(TestEqualUnequal, TestUnequalPatterns_1){
    patterns test_1 = patterns("+a->b+"), test_2 = patterns("a->b+");

    ASSERT_TRUE(test_1 != test_2);
}
TEST(TestEqualUnequal, TestUnequalPatterns_2){
    patterns test_1 = patterns("+a->b+;+b->a+"), test_2 = patterns("+a->b+;+b->a+");

    ASSERT_FALSE(test_1 != test_2);
}
TEST(TestEqualUnequal, TestUnequalPatterns_3){
    patterns test_1 = patterns("+a->b+;+b->a+"), test_2 = patterns("+a->b+");

    ASSERT_TRUE(test_1 != test_2);
}

TEST(TestEqualUnequal, TestEqualMachine_1){
    machine test_1 = machine("abab", "+a->b+;+b->a+"), test_2 = machine("abab", "+a->b+;+b->a+");

    ASSERT_TRUE(test_1 == test_2);
}
TEST(TestEqualUnequal, TestEqualMachine_2){
    machine test_1 = machine("aaaa", "+a->b+;+b->a+"), test_2 = machine("abab", "+a->b+;+b->a+");

    ASSERT_FALSE(test_1 == test_2);
}
TEST(TestEqualUnequal, TestEqualMachine_3){
    machine test_1 = machine("abab", "+a->b+"), test_2 = machine("abab", "+a->b+;+b->a+");

    ASSERT_FALSE(test_1 == test_2);
}

TEST(TestEqualUnequal, TestUnequalMachine_1){
    machine test_1 = machine("abab", "+a->b+;+b->a+"), test_2 = machine("abab", "+a->b+;+b->a+");

    ASSERT_FALSE(test_1 != test_2);
}
TEST(TestEqualUnequal, TestUnequalMachine_2){
    machine test_1 = machine("aaaa", "+a->b+;+b->a+"), test_2 = machine("abab", "+a->b+;+b->a+");

    ASSERT_TRUE(test_1 != test_2);
}
TEST(TestEqualUnequal, TestUnequalMachine_3){
    machine test_1 = machine("abab", "+a->b+"), test_2 = machine("abab", "+a->b+;+b->a+");

    ASSERT_TRUE(test_1 != test_2);
}


TEST(TestPatternsFunctions, TestDeletePattern_1){
    patterns test_1 = patterns("+a->b+;+b->a+;+->|;->+"), test_2 = patterns("+a->b+;+->|;->+");
    test_1.delete_pattern("+b->a+");

    ASSERT_TRUE(test_1 == test_2);
}

TEST(TestPatternsFunctions, TestDeletePattern_2){
    patterns test_1, test_2;
    test_1.delete_pattern("+b->a+");

    ASSERT_TRUE(test_1 == test_2);
}
TEST(TestPatternsFunctions, TestDeletePattern_3){
    patterns test_1 = patterns("+a->b+;+b->a+;+->|;->+"), test_2 = patterns("+a->b+;+b->a+;+->|");
    test_1.delete_pattern("->+");

    ASSERT_TRUE(test_1 == test_2);
}
TEST(TestPatternsFunctions, TestPushBackPattern_1){
    patterns test_1, test_2 = patterns("+a->b+");
    test_1.push_back("+a->b+");

    ASSERT_TRUE(test_1 == test_2);
}
    TEST(TestPatternsFunctions, TestPushBackPattern_2){
    patterns test_1 = patterns("+a->b+"), test_2 = patterns("+a->b+;+b->a+");
    test_1.push_back("+b->a+");

    ASSERT_TRUE(test_1 == test_2);
}
TEST(TestPatternsFunctions, TestViewPatterns){
    patterns test_1 = patterns("+a->b+;+b->a+;+->|;->+");

    ASSERT_NO_THROW(test_1.view_patterns());
}


TEST(TestStreams, TestIstreamPatterns){
    patterns rules;
    std::stringstream ss; ss << "+a->b+;+b->a+;+->|;->+";

    ASSERT_NO_THROW(ss >> rules);
}
TEST(TestStreams, TestOstreamPatterns){
    patterns rules = patterns("+a->b+;+b->a+;+->|;->+") ;

    ASSERT_NO_THROW(std::cout << rules);
}


TEST(TestRibbon, TestSetRibbon){
    machine m;
    m.set_ribbon("qwerty");

    ASSERT_NO_THROW(std::cout<<m.get_ribbon()<<std::endl);
}
TEST(TestRibbon, TestChangeRibbon){
    machine m = machine("aaa","a->b");
    m.set_ribbon("qwerty");

    ASSERT_NO_THROW(std::cout<<m.get_ribbon()<<std::endl);
}


TEST(CorrectOperation, TestStart_1){
    machine m = machine("aaabbbaba", "+a->b+;+b->a+;+->|;->+");
    m.start(false);
    ASSERT_EQ("bbbaaabab", m.get_ribbon());
}
TEST(CorrectOperation, TestStart_2){
    machine m = machine("bbbbaabb", "aa->a;bb->b");
    m.start(false);
    ASSERT_EQ("bab", m.get_ribbon());
}
TEST(CorrectOperation, TestStart_3){
    machine m = machine("aaabbba", "*a->a*;*b->b*;a*->aa|;b*->bb|;*->|;->*");
    m.start(false);
    ASSERT_EQ("aaabbbaa", m.get_ribbon());
}

TEST(CorrectOperation, TestStep){
    machine m = machine("aaabbbaba", "+a->b+;+b->a+;+->|;->+");
    m.step();

    ASSERT_EQ("+aaabbbaba", m.get_ribbon());
}

TEST(InputFromFile, Test_1){
    std::ifstream in;

    in.open("patterns");
    patterns p; in >> p;
    in.close();
    in.open("ribbon");
    std::string str; in>>str;
    in.close();

    machine m =machine(str, p);
    m.start(false);
    ASSERT_EQ("bbbaaabab", m.get_ribbon());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
