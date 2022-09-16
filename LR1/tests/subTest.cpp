#include "extraFunc.cpp"

TEST(subTest, default)
{

    Normal_matrix matrix, subMatrix;
    vector<vector<double>> tmp, sub;

    for(auto i = 0; i < 5; i++)
    {

        tmp = randomFill(5, 5, 32);
        matrix.set(tmp);

        pair<cu_int, cu_int> a(2, 3), b(3, 4);
        sub = {
            {tmp[2][3], tmp[2][4]},
            {tmp[3][3], tmp[3][4]}
        };

        subMatrix.set(sub);
        EXPECT_EQ(matrix.sub(a, b), subMatrix);

    }

    Normal_matrix temp(
        {
            {1, 5, 3},
            {1, 2, 3},
            {1, 9, 3}
        }
    );
    pair<cu_int, cu_int> a(1, 1), b(1, 1);

    subMatrix.set({{2}});
    EXPECT_EQ(temp.sub(a, b), subMatrix);

}

TEST(subTest, empty)
{

    pair<cu_int, cu_int> a(0, 0), b(0, 0);
    Normal_matrix tmp;

    EXPECT_THROW(tmp.sub(a, b), const char*);

}

TEST(subTest, invalid_angles)
{

    Normal_matrix tmp(
        {
            {1, 2, 3},
            {1, 2, 3},
            {1, 2, 3}
        }
    );
    pair<cu_int, cu_int> a1(1, 1), b1(0, 0);

    EXPECT_THROW(tmp.sub(a1, b1), const char*);

    pair<cu_int, cu_int> a2(1, 1), b2(3, 2);

    EXPECT_THROW(tmp.sub(a1, b2), const char*);

    pair<cu_int, cu_int> a3(1, 1), b3(2, 3);

    EXPECT_THROW(tmp.sub(a3, b3), const char*);

}