#include "Normal_matrix.h"
/**
 * @file types.cpp
 * @author Yakavinich Hleb (gleb.yakovinich1990@gmail.com)
 * @brief functions to check type of matrix
 * @date 2022-09-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//#include "src/Normal_matrix.h"

/**
 * @brief check if matrix IS square matrix
 * 
 * @param forCheck matrix for check
 * @return true if matrix is square
 * @return false if matrix isn't square
 */
bool squareMatrix(Normal_matrix forCheck)
{

    return forCheck.get().size() == forCheck.get().at(0).size();

}

/**
 * @brief check if matrix IS zero matrix
 * 
 * @param forCheck  matrix for check
 * @return true if matrix is zero matrix
 * @return false if matrix isn't zero matrix
 */
bool zeroMatrix(Normal_matrix forCheck)
{

    for(auto i = 0; i < forCheck.get().size(); i++)
        for(auto j = 0; j < forCheck.get().at(0).size(); j++)
            if(forCheck.get().at(i).at(j) != 0)
                return 0;

    return 1;

}

/**
 * @brief check if matrix IS diagonal matrix
 * 
 * @param forCheck matrix for check
 * @return true if matrix is diagonal
 * @return false if matrix isn't diagonal
 */
bool diagonalMatrix(Normal_matrix forCheck)
{

    Normal_matrix temp1(forCheck.get().size(), forCheck.get().at(0).size());
    Normal_matrix temp2 = temp1, zero_matrix = temp1;

    for(auto i = 0; i < forCheck.get().size(); i++)
        for(auto j = 0; j < forCheck.get().at(0).size(); j++)
        {
            if(i == j)
                temp1.at(i, j) = forCheck.get().at(i).at(j);

            if(forCheck.get().size() - i - 1 == j)
                temp2.at(i, j) = forCheck.get().at(i).at(j);
        }

    return (temp1 - forCheck == zero_matrix) or (temp2 - forCheck == zero_matrix);

}

/**
 * @brief check if matrix IS single matrix
 * 
 * @param forCheck matrix for check
 * @return true if matrix is single matrix
 * @return false if matrix isn't single matrix 
 */
bool singleMatrix(Normal_matrix forCheck)
{

    for(auto i = 0; i < forCheck.get().size(); i++)
        for(auto j = 0; j < forCheck.get().at(0).size(); j++)
            if(forCheck.get().at(i).at(j) != 1)
                return 0;

    return 1;

}

/**
 * @brief check if matrix IS symmetric matrix
 * 
 * @param forCheck matrix for check
 * @return true if matrix is symmetric matrix
 * @return false if matrix isn't symmetric matrix
 */
bool symmetricMatrix(Normal_matrix forCheck)
{

    return forCheck == forCheck.transpose();

}

/**
 * @brief check if matrix IS top triangle matrix
 * 
 * @param forCheck matrix for check
 * @return true if matrix is top triangle matrix
 * @return false if matrix isn't top triangle matrix
 */
bool topTriangleMatrix(Normal_matrix forCheck)
{

    cu_int size = forCheck.get().size();
    Normal_matrix temp1(size, size);
    Normal_matrix temp2 = temp1;

    for(auto i = 0; i < size; i++)
        for(auto j = 0; j < size; j++)
        {
            if(size - 1 - j + i <= size - 1)
                temp1.at(i, j) = forCheck.get().at(i).at(j);

            if(i + j <= size - 1)
                temp2.at(i, j) = forCheck.get().at(i).at(j);
        }

    return (temp1 == forCheck) or (temp2 == forCheck);

}

/**
 * @brief check if matrix IS bottom triangle matrix
 * 
 * @param forCheck matrix for check
 * @return true if matrix is bottom triangle matrix
 * @return false if matrix isn't bottom triangle matrix
 */
bool bottomTriangleMatrix(Normal_matrix forCheck)
{

    cu_int size = forCheck.get().size();
    Normal_matrix temp1(size, size);
    Normal_matrix temp2 = temp1;

    for(auto i = 0; i < size; i++)
        for(auto j = 0; j < size; j++)
        {
            if(2*size - 2 - i - j <= size - 1)
                temp1.at(i, j) = forCheck.get().at(i).at(j);

            if(size - 1 - j + i <= size - 1)
                temp2.at(i, j) = forCheck.get().at(i).at(j);
        }

    return (temp1 == forCheck) or (temp2 == forCheck);

}

