#include "extraFunc.cpp"

TEST(resizeTest, empty)
{

    Normal_matrix tmp, empty;
    tmp.resizeCols(5);

    EXPECT_EQ(empty, tmp);

    tmp.resizeRows(5);

    EXPECT_EQ(empty, tmp);

}

TEST(resizeTest, invalid)
{

    Normal_matrix tmp;

    EXPECT_THROW(tmp.resizeCols(-5), const char*);

    EXPECT_THROW(tmp.resizeRows(-5), const char*);

}

TEST(resizeTest, default)
{

    vector<vector<double>> tmp({{1}});
    Normal_matrix matrix(tmp);

    for(int i = 0; i < 5; i++)
    {

    int resizeNum = rand() % 3;
    matrix.resizeCols(resizeNum, 1);
    for(auto i = 0; i < tmp.size(); i++)
        tmp.at(i).resize(tmp.at(i).size() + resizeNum, 1);

    matrix.resizeRows(resizeNum, 1);
    tmp.resize(tmp.size() + resizeNum, tmp.at(0));
    EXPECT_EQ(matrix.get(), tmp);

    }

}
