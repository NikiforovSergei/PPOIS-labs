#include "polynominal/polynominal.hpp"

#include "gtest/gtest.h"

namespace {
  TEST(OperationsWithPolynominal, Sum) {
    auto p1 = Polynominal({1, 2, 3}), p2 = Polynominal({3, 4, 5});
    auto res = Polynominal({4, 6, 8}); 

    EXPECT_EQ(p1 + p2, res);
  }

  TEST(OperationsWithPolynominal, Diff) {
    auto p1 = Polynominal({5, 4, 3}), p2 = Polynominal({1, 2, 3});
    auto res = Polynominal({4, 2, 0}); 

    EXPECT_EQ(p1 - p2, res);
  }

  TEST(OperationsWithPolynominal, Mult) {
    auto p1 = Polynominal({1, 2}), p2 = Polynominal({3, 4});
    auto res = Polynominal({3, 10, 8}); 

    EXPECT_EQ(p1 * p2, res);
  }

  TEST(SolvePolynominal, Solve) {
    auto p = Polynominal({1, 2});
    auto res = p(2);

    EXPECT_EQ(res, 5);
  }

  TEST(GetFieldPolynominal, Get) {
    auto p = Polynominal({1, 2});
    auto res = p[0];

    EXPECT_EQ(res, 1);
  }
}

