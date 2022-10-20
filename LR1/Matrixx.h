#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

/*! This class is used to operate with matrixies*/

namespace MMM
{
    class Matrixx
    {
    public:
        /// Command for entering matrix from the file.
        /// @param file This represents name of the file with a matrix.
        /// @returns Nothing important.
        void enter(string file); 

        /*! Command for printing the matrix on the screen. */
        /// @param No parameters.
        /// @returns Nothing important.
        void print();

        /*! Command for incrementing matrix.*/
        /// @param No parameters.
        /// @returns Nothing important.
        void operator ++();

        /*! Command for post-incrementing matrix. */
        /// @param No parameters.
        /// @returns Nothing important.
        void operator ++(int);

        /*! Command for decrementing matrix.. */
        /// @param No parameters.
        /// @returns Nothing important.
        void operator --();

        /*! Command for post-decrementing matrix. */
        /// @param No parameters.
        /// @returns Nothing important.
        void operator --(int);

        /*! Command for adding to the matrix the <radok> column, if a = 1, or the <radok> row. */
        /// @param a represents the key for adding a coloumn.
        /// @param b represents the key for adding a row.
        /// @param radok represents the added line.
        /// @returns Nothing important.
        void add(bool a, bool b, vector<int> radok);

        /*! Command for deleting the last column, if a = 1, or the row from matrix. */
        /// @param a represents the key for deleting a coloumn.
        /// @param b represents the key for deleting a row.
        /// @returns Nothing important.
        void del(bool a, bool b);

        /*! Command for extracting submatrix from the matrix.
        * Which consists of original matrix's elements starting with element with coordinates x1 and y1,
        * ending with x2, y2, and all elements between them.*/
        /// @param x1 is a row coordinate of the left extracted matrix's corner.
        /// @param y1 is a column coordinate of the left extracted matrix's corner.
        /// @param x2 is a row coordinate of the right extracted matrix's corner.
        /// @param y2 is a column coordinate of the right extracted matrix's corner.
        /// @returns Nothing important.
        void extract(int x1, int y1, int x2, int y2);

        /*! Command for defining the type of matrix. */
        /// @param No parameters.
        /// @returns string that consists of words defining the matrix's type.
        string type();

        /*! Command for transponating matrix. */
        /// @param No parameters.
        /// @returns Nothing important.
        void trans();

        vector<vector<int>> vector_return();

        void operator +(Matrixx m2);
    };
}