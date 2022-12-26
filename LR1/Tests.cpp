#include <gtest/gtest.h>
#include "header.h"

//арифметические операции
class Addition : public ::testing::Test {
public:
    string s = "100000000000000000000000000";
    Long l1 = s;
    Long l2 = s;
    int i = 10;
};
class Multiplication : public ::testing::Test {
public:
    string s = "100000000000000000000000000";
    Long l1 = s;
    Long l2 = s;
    int i = 10;
};
class Division : public ::testing::Test {
public:
    string s = "22222222222222222222222";
    Long l1 = s;
    Long l2 = s;
    int i = 2;
};
class Subtraction : public ::testing::Test {
public:
    string s = "100000000000000000000000000";
    Long l1 = s;
    Long l2 = s;
    int i = 10;
};

class Compare : public ::testing::Test {
public:
    string s1, s2;
    Long l1 = s1 = "1000000000";
    Long l2 = s2 = "1000000000000000000000000";
    int i = 10;
};

class KreMent : public ::testing::Test {
public:
    Long l1 = -123;
};


//длинные
TEST_F(Addition, Long) {
    Long l3("200000000000000000000000000");
    EXPECT_EQ(l3, l1 + l2);
}
TEST_F(Division, Long) {
    Long l3("1");
    EXPECT_EQ(l3, l1 / l2);
}
TEST_F(Subtraction, Long) {
    Long l3 = l1 - l2;
    cout << l3;
    EXPECT_EQ(0, l1 - l2);
}
TEST_F(Multiplication, Long) {
    Long l3("10000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(l3, l1 * l2);
}

//целые
TEST_F(Addition, Int) {
    Long l3("100000000000000000000000010");
    EXPECT_EQ(l3, l1 + i);
}
TEST_F(Division, Int) {
    Long l3("11111111111111111111111");
    Long l2 = l1/i;
    cout << l2;
    EXPECT_EQ(l3, l1 / i);
}
TEST_F(Subtraction, Int) {
    Long l3("99999999999999999999999990");
    cout << l3;
    EXPECT_EQ(l3, l1 - i);
}
TEST_F(Multiplication, Int) {
    Long l3("1000000000000000000000000000");
    EXPECT_EQ(l3, l1 * i);
}

//короткое сравнение
//длинные
TEST_F(Addition, AppropriationLong) {
    l1+=l2;
    Long l3("200000000000000000000000000");
    EXPECT_EQ(l3, l1);
}
TEST_F(Division, AppropriationLong) {
    l1/=l2;
    Long l3("1");
    EXPECT_EQ(l3, l1);
}
TEST_F(Subtraction, AppropriationLong) {
    l1-=l2;
    Long l3("0");
    EXPECT_EQ(l3, l1);
}
TEST_F(Multiplication, AppropriationLong) {
    l1*=l2;
    Long l3("10000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(l3, l1);
}
//целые
TEST_F(Addition, AppropriationInt) {
    l1+=i;
    Long l3("100000000000000000000000010");
    EXPECT_EQ(l3, l1);
}
TEST_F(Division, AppropriationInt) {
    l1/=i;
    Long l3("11111111111111111111111");
    EXPECT_EQ(l3, l1);
}
TEST_F(Subtraction, AppropriationInt) {
    l1-=i;
    Long l3("99999999999999999999999990");
    EXPECT_EQ(l3, l1);
}
TEST_F(Multiplication, AppropriationInt) {
    l1 *= i;
    Long l3("1000000000000000000000000000");
    EXPECT_EQ(l3, l1);
};
TEST(Dec, Post){
    Long l = 123;
    l++;
    EXPECT_EQ(124, l);
};
TEST(Dec, Pre){
    Long l = 123;
    ++l;
    EXPECT_EQ(124, l);
};
TEST(Incr, Post){
    Long l = 123;
    l--;
    EXPECT_EQ(122, l);
};
TEST(Incr, Pre){
    Long l = 123;
    --l;
    EXPECT_EQ(122, l);
};

//сравнение длинные
TEST_F(Compare, MoreLong) {
    EXPECT_EQ(0, l1 > l2);
};
TEST_F(Compare, MoreEqLong) {
    EXPECT_EQ(0, l1 >= l2);
};
TEST_F(Compare, LessLong) {
    EXPECT_EQ(1, l1 < l2);
};
TEST_F(Compare, LessEqLong) {
    EXPECT_EQ(1, l1 <= l2);
};

//целые сравнение
TEST_F(Compare, MoreInt) {
    EXPECT_EQ(1, l1 > i);
};
TEST_F(Compare, MoreEqInt) {
    EXPECT_EQ(1, l1 >= i);
};
TEST_F(Compare, LessInt) {
    EXPECT_EQ(0, l1 < i);
};
TEST_F(Compare, LessEqInt) {
    EXPECT_EQ(0, l1 <= i);
};