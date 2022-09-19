#include "pch.h"
#include "../lab1_sem3/Fraction.cpp"

struct FractionTest : testing::Test
{
	Fraction* f;
	Fraction* otherPlus;
	Fraction* otherMinus;
	Fraction* zero;
	FractionTest()
	{
		f = new Fraction(7, 5, 1);
		otherPlus = new Fraction(4, 3, 0);
		otherMinus = new Fraction(-4, 3, 0);
		zero = new Fraction(0, 1, 0);
	}
	~FractionTest()
	{
		delete f;
		delete otherPlus;
		delete otherMinus;
		delete zero;
	}
};
TEST_F(FractionTest, FractionSumTest) {
	Fraction answer_1(11, 15, 3);
	Fraction answer_2(1, 15, 1);
	Fraction answer_3(2, 5, 3);
	Fraction answer_4(2, 5, 1);
	EXPECT_EQ(true, answer_1 == *f + *otherPlus);
	EXPECT_EQ(true, answer_2 == *f + *otherMinus);
	EXPECT_EQ(true, answer_3 == *f + 1);
	EXPECT_EQ(true, answer_4 == *f + -1);
}

TEST_F(FractionTest, FractionSumWithAssignmentTest) {
	Fraction answer_1(11, 15, 3);
	Fraction answer_2(1, 15, 1);
	Fraction answer_3(2, 5, 3);
	Fraction answer_4(2, 5, 1);
	Fraction temp_1(*f);
	temp_1 += *otherPlus;
	Fraction temp_2(*f);
	temp_2 += *otherMinus;
	Fraction temp_3(*f);
	temp_3 += 1;
	Fraction temp_4(*f);
	temp_4 += -1;
	EXPECT_EQ(true, answer_1 == temp_1);
	EXPECT_EQ(true, answer_2 == temp_2);
	EXPECT_EQ(true, answer_3 == temp_3);
	EXPECT_EQ(true, answer_4 == temp_4);
}

TEST_F(FractionTest, FractionSubTest) {
	Fraction answer_1(1, 15, 1);
	Fraction answer_2(11, 15, 3);
	Fraction answer_3(2, 5, 1);
	Fraction answer_4(2, 5, 3);
	EXPECT_EQ(true, answer_1 == *f - *otherPlus);
	EXPECT_EQ(true, answer_2 == *f - *otherMinus);
	EXPECT_EQ(true, answer_3 == *f - 1);
	EXPECT_EQ(true, answer_4 == *f - -1);
}

TEST_F(FractionTest, FractionSubWithAssignmentTest) {
	Fraction answer_1(1, 15, 1);
	Fraction answer_2(11, 15, 3);
	Fraction answer_3(2, 5, 1);
	Fraction answer_4(2, 5, 3);
	Fraction temp_1(*f);
	temp_1 -= *otherPlus;
	Fraction temp_2(*f);
	temp_2 -= *otherMinus;
	Fraction temp_3(*f);
	temp_3 -= 1;
	Fraction temp_4(*f);
	temp_4 -= -1;
	EXPECT_EQ(true, answer_1 == temp_1);
	EXPECT_EQ(true, answer_2 == temp_2);
	EXPECT_EQ(true, answer_3 == temp_3);
	EXPECT_EQ(true, answer_4 == temp_4);
}
TEST_F(FractionTest, FractionMultTest) {
	Fraction answer_1(1, 5, 3);
	Fraction answer_2(-1, 5, 3);
	Fraction answer_3(4, 5, 4);
	Fraction answer_4(0, 5, 0);
	Fraction answer_5(0, 5, 0);
	EXPECT_EQ(true, answer_1 == *f * *otherPlus);
	EXPECT_EQ(true, answer_2 == *f * *otherMinus);
	EXPECT_EQ(true, answer_3 == *f * 2);
	EXPECT_EQ(true, answer_4.GetNumeration() == (*f * *zero).GetNumeration());
	EXPECT_EQ(true, answer_5.GetNumeration() == (*f * 0).GetNumeration());
}
TEST_F(FractionTest, FractionMultWithAssignmentTest) {
	Fraction answer_1(1, 5, 3);
	Fraction answer_2(-1, 5, 3);
	Fraction answer_3(4, 5, 4);
	Fraction answer_4(0, 5, 0);
	Fraction answer_5(0, 5, 0);
	Fraction temp_1(*f);
	temp_1 *= *otherPlus;
	Fraction temp_2(*f);
	temp_2 *= *otherMinus;
	Fraction temp_3(*f);
	temp_3 *= 2;
	Fraction temp_4(*f);
	temp_4 *= *zero;
	Fraction temp_5(*f);
	temp_5 *= 0;
	EXPECT_EQ(true, answer_1 == temp_1);
	EXPECT_EQ(true, answer_2 == temp_2);
	EXPECT_EQ(true, answer_3 == temp_3);
	EXPECT_EQ(true, answer_4.GetNumeration() == temp_4.GetNumeration());
	EXPECT_EQ(true, answer_5.GetNumeration() == temp_5.GetNumeration());
}

TEST_F(FractionTest, FractionDivtTest) {
	Fraction answer_1(4, 5, 1);
	Fraction answer_2(-4, 5, 1);
	Fraction answer_3(1, 5, 1);
	Fraction answer_4(7, 5, 1);
	Fraction answer_5(7, 5, 1);
	EXPECT_EQ(true, answer_1 == *f / *otherPlus);
	EXPECT_EQ(true, answer_2 == *f / *otherMinus);
	EXPECT_EQ(true, answer_3 == *f / 2);
	EXPECT_EQ(true, answer_4.GetNumeration() == (*f / *zero).GetNumeration());
	EXPECT_EQ(true, answer_5.GetNumeration() == (*f / 0).GetNumeration());
}

TEST_F(FractionTest, FractionDivtWithAssignmentTest) {
	Fraction answer_1(4, 5, 1);
	Fraction answer_2(-4, 5, 1);
	Fraction answer_3(1, 5, 1);
	Fraction answer_4(7, 5, 1);
	Fraction answer_5(7, 5, 1);
	Fraction temp_1(*f);
	temp_1 /= *otherPlus;
	Fraction temp_2(*f);
	temp_2 /= *otherMinus;
	Fraction temp_3(*f);
	temp_3 /= 2;
	Fraction temp_4(*f);
	temp_4 /= *zero;
	Fraction temp_5(*f);
	temp_5 /= 0;
	EXPECT_EQ(true, answer_1 == temp_1);
	EXPECT_EQ(true, answer_2 == temp_2);
	EXPECT_EQ(true, answer_3 == temp_3);
	EXPECT_EQ(true, answer_4.GetNumeration() == temp_4.GetNumeration());
	EXPECT_EQ(true, answer_5.GetNumeration() == temp_5.GetNumeration());
}

TEST_F(FractionTest, FractionÑompareTest) {
	EXPECT_EQ(true, Fraction(7, 5, 2) > *f);
	EXPECT_EQ(false, Fraction(7, 5, 2) < *f);
	EXPECT_EQ(true, Fraction(7, 5, 1) <= *f);
	EXPECT_EQ(false, Fraction(7, 5, 0) >= *f);
	EXPECT_EQ(true, *f < 3);
	EXPECT_EQ(false, *f > 3);
	EXPECT_EQ(true, *f >= 2);
	EXPECT_EQ(false, *f <= 2);
	EXPECT_EQ(false, *f == 2);
	EXPECT_EQ(true, *f != Fraction(7, 5, 2));
	EXPECT_EQ(false, *f == Fraction(7, 5, 2));
	EXPECT_EQ(true, *f != 2);
}

TEST_F(FractionTest, FractionToDoubleTest) {
	double a = 12.0, b = 5.0, c = 4.0, d = 3.0, e = -4.0;
	EXPECT_EQ(a / b, f->ToDouble());
	EXPECT_EQ(c / d, otherPlus->ToDouble());
	EXPECT_EQ(e / d, otherMinus->ToDouble());
}

