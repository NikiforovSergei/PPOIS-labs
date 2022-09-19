#include "extraFunc.cpp"

TEST(setTest, empty)
{

    Normal_matrix tmp;
    
    tmp.set({});
    vector<vector<double>> tmpVec({});

    EXPECT_EQ(tmp.get(), tmpVec);

}

TEST(setTest, invalid)
{

    vector<vector<double>> tmp1(
        {
            {1, 2, 3},
            {1, 2, 3, 4},
            {1, 2, 3}
        }
    );

    Normal_matrix matrix;

    EXPECT_THROW(matrix.set(tmp1), const char*);
    
}

TEST(setTest, default)
{

    Normal_matrix temp_matrix;
    vector<Normal_matrix> matrixes; 
    vector<vector<double>> tmp;

    for(auto i = 0; i < 5; i++)
    {

        tmp = randomFill(5, 5, 32);
        temp_matrix.set(tmp);

        matrixes.push_back(temp_matrix);

        EXPECT_EQ(matrixes.at(i).get(), tmp);

    }

}