#include "extraFunc.cpp"

TEST(determinantTest, empty)
{

    Normal_matrix tmp;
    EXPECT_THROW(tmp.determinant(), const char*);

}

TEST(determinantTest, invalid)
{

    Normal_matrix tmp(3, 4, 12);
    EXPECT_THROW(tmp.determinant(), const char*);

}

TEST(determinantTest, default)
{

    Normal_matrix tmp1(
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    ), tmp2(
        {
            {4, 51, 2},
            {5, 23, 1},
            {5, 2, 5}
        }
    ), tmp3(
        {
            {9, 11, 2},
            {5, 93, 1},
            {1, 5, 5}
        }
    );

    EXPECT_EQ(tmp1.determinant(), 0);
    EXPECT_EQ(tmp2.determinant(), -778);
    EXPECT_EQ(tmp3.determinant(), 3740);

}