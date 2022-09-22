#include "fraction/fraction.hpp"

#include "gtest/gtest.h"

namespace {
  TEST(ComparisonFraction, EqualsFraction) {
    auto f1 = Fraction(1, 2), f2 = Fraction(1, 2);
    EXPECT_EQ(f1, f2);
  }

  TEST(ComparisonFraction, GreaterFraction) {
    auto f1 = Fraction(1, 2), f2 = Fraction(1, 3);
    EXPECT_GT(f1, f2); 
  }
  
  TEST(ComparisonFraction, LessFraction) {
    auto f1 = Fraction(1, 3), f2 = Fraction(1, 2);
    EXPECT_LT(f1, f2);
  }
  
  TEST(ComparisonFraction, GreaterInt) {
    Fraction f1 = Fraction(5, 4);
    int f2 = 1;

    EXPECT_GT(f1, f2);
  }

  TEST(ComparisonFraction, LessInt) {
    Fraction f1 = Fraction(1, 4);
    int f2 = 1;

    EXPECT_LT(f1, f2);
  }

  TEST(OperatorFraction, Sum) {
    auto f1 = Fraction(1, 2), f2 = Fraction(1, 2);

    EXPECT_EQ(f1 + f2, Fraction(1, 1));
  }

  TEST(OperatorFraction, Difference) {
    auto f1 = Fraction(3, 2), f2 = Fraction(1, 2);

    EXPECT_EQ(f1 - f2, Fraction(1, 1));
  }

  TEST(OperatorFraction, Multiplication) {
    auto f1 = Fraction(1, 2), f2 = Fraction(1, 2);

    EXPECT_EQ(f1 * f2, Fraction(1, 4));
  }

  TEST(OperatorFraction, Fraction) {
    auto f1 = Fraction(1, 2), f2 = Fraction(1, 2);

    EXPECT_EQ(f1 / f2, Fraction(1, 1));
  }
}
