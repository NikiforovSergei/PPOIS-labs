#include "extraFunc.cpp"

TEST(mathOperators, plus_minus_incompatible)
{

    Normal_matrix tmp1(2, 3, 5), tmp2(1, 2, 4);

    EXPECT_THROW(tmp1 + tmp2, const char*);
    EXPECT_THROW(tmp1 - tmp2, const char*);

}

TEST(mathOperators, multiply_default)
{

    vector<vector<double>> fst(
        {
            {1, 2, 3, 4},
            {1, 2, 3, 4}
        }
    ),
                  snd(
        {
            {6, 2},
            {4, 8},
            {33, 1},
            {1, 1},
            {11, 1},
            {1, 11}
        }
    );
    vector<vector<double>> res(
        {
            {8, 16, 24, 32},
            {12, 24, 36, 48},
            {34, 68, 102, 136},
            {2, 4, 6, 8},
            {12, 24, 36, 48},
            {12, 24, 36, 48}
        }
    );

    Normal_matrix abc1(snd), abc2(fst), resMatrix = abc1*abc2; 

    EXPECT_EQ(resMatrix.get() , res);
}

TEST(mathOperators, multiply_incompatible)
{

    Normal_matrix tmp1(3, 3, 5), tmp2(1, 2, 4);

    EXPECT_THROW(tmp1 * tmp2, const char*);

}

