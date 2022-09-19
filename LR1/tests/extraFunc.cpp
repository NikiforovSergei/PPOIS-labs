#include "Normal_matrix_rel.cpp"
#include<gtest/gtest.h>

inline vector<vector<double>> randomFill(cu_int cols, cu_int rows, cu_int seed)
{

    srand(seed);
    vector<double> tempRow(cols, 0);
    vector<vector<double>> temp;
    for(auto j = 0; j < rows; j++) 
    {
        for(auto i = 0; i < cols; i++)
            tempRow.at(i) = rand();

        temp.push_back(tempRow);
    }
    return temp;

}