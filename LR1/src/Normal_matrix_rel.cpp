/**
 * @file Normal_matrix_rel.cpp
 * @author Yakavinich Hleb (gleb.yakovinich1990@gmail.com)
 * @brief   realization class Normal matrix, which realize mathematic matrix and some methods for it
 * @date 2022-09-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//#ifdef NO_MULTIPLE_DEFINE

#include "Normal_matrix.h"
using namespace std;

inline void Normal_matrix::set
(const vector<vector<double>>& newMatrix)
{
       
    this->matrix = newMatrix;

    if( !this->isValid() )
        throw "matrix isn't valid";

}   

inline
vector<vector<double>> Normal_matrix::get
()
{

    return this->matrix;

}

inline
Normal_matrix Normal_matrix::sub
(pair<cu_int, cu_int> _Angle1, pair<cu_int, cu_int> _Angle2)
{

    if( !isTrueAngle(_Angle1, _Angle2) )
        throw "Incorrect angles. _Angle1 should be top-left, _Angle2 -- bottom-right";

    vector<vector<double>> subMatrix;
    vector<double> subRow(_Angle2.second - _Angle1.second + 1, 0);

    for_each(matrix.begin() + _Angle1.first,
            matrix.begin() + _Angle2.first + 1,
            [&](auto it)
            {

                copy(it.begin()+_Angle1.second,
                     it.begin()+_Angle2.second + 1,
                     subRow.begin());
                subMatrix.push_back(subRow);

            }
            );

    Normal_matrix ret(subMatrix);
    return ret;

}

inline
bool Normal_matrix::isTrueAngle
(pair<cu_int, cu_int> _Angle1, pair<cu_int, cu_int> _Angle2)
{

    if( _Angle2.first < matrix.size() )
        if( _Angle2.second < matrix.at(0).size() )
            if( _Angle1.first <= _Angle2.first )
                if(_Angle1.second <= _Angle2.second )
                    return 1;

    return 0;

}

inline
bool Normal_matrix::isValid
() const
{

    for(auto it = matrix.begin(); it != matrix.end(); it++)
        if((*it).size() != matrix.at(0).size())
            return 0;

    return 1;

}

inline
bool Normal_matrix::isCompatible
(const Normal_matrix& with) const
{

    if(this->matrix.size() == 0 and with.matrix.size() == 0)
        return 1;

    return (this->matrix.size() == with.matrix.size() 
            and this->matrix.at(0).size() == with.matrix.at(0).size());

}

inline
Normal_matrix::Normal_matrix
(cu_int colsNum, cu_int rowsNum, const double fillWith)
{

    if(colsNum == 0)
        return;

    vector<double> temp(colsNum, fillWith);
    vector<vector<double>> newMatrix(rowsNum, temp);

    matrix = newMatrix;
    if( !isValid() )
        throw "matrix ins't valid";

}

inline
Normal_matrix::Normal_matrix
(const vector<vector<double>>& newMatrix)
{

    if( newMatrix.size() != 0 )
        if( newMatrix.at(0).size() == 0)
            return;

    this->matrix = newMatrix;

    if( !this->isValid() )
        throw "matrix isn't valid";

}

inline
Normal_matrix::~Normal_matrix
()
{

   

}

inline
Normal_matrix::Normal_matrix
()
{}

inline
istream& operator>>
(istream& in, Normal_matrix& to)
{ 

    unsigned int cols = 0, rows = 0;

    cin >> cols >> rows;

    for(int j = 0; j < rows; j++)
    {

        vector<double> tempRowVec;
        for (int i = 0; i < cols; i++)
        {

            double cell;
            in >> cell;
            tempRowVec.push_back(cell);

        }
        to.matrix.push_back(tempRowVec);

    } 

    if( !to.isValid() )
        throw "matrix isn't valid";
        
    return in;

}

inline
ostream& operator<<
(ostream& out, const Normal_matrix& from)
{

    for(auto i = 0; i < from.matrix.size(); i++)
    {

        for(auto j = 0; j < from.matrix.at(i).size(); j++)
            out << from.matrix.at(i).at(j)
                << (j + 1 == from.matrix.at(i).size() ? "" : " ");

        out << (i + 1 == from.matrix.size() ? "\0" : "\n");

    }
    return out;

}

inline
ifstream& operator>>
(ifstream& in, Normal_matrix& to)
{ 

    string tempRow;
    while(getline(in, tempRow))
    {
        if(tempRow.at(0) == '#')
            continue;
    
        stringstream streamRow;
        streamRow << tempRow;
        string cellstr;
        vector<double> tempRowVec;
        
        while(streamRow >> cellstr)
            tempRowVec.push_back( stod(cellstr) );

        to.matrix.push_back(tempRowVec);

    } 
    
    if( !to.isValid() )
        throw "matrix isn't valid";
        
    return in;

}

inline
void Normal_matrix::resizeCols
(const int colsNum, const double fillWith)
{

    if( matrix.size() == 0)
    {
        if(colsNum < 0)
            throw "Number of cols cannot be less then 0";
        else
            return;
    }

    if( matrix.at(0).size() + colsNum < 0 )
        throw "Number of cols cannot be less then 0";

    for(auto i = 0; i < matrix.size(); i++)
        matrix.at(i).resize(matrix.at(i).size() + colsNum, fillWith);

}

inline
void Normal_matrix::resizeRows
(const int rowsNum, const double fillWith)
{

    if( matrix.size() == 0)
    {
        if(rowsNum < 0)
            throw "Number of cols cannot be less then 0";
        else
            return;
    }

    if(matrix.size() + rowsNum < 0)
        throw "Number of cols cannot be less then 0";

    vector<double> temp(matrix.at(0).size(), fillWith);
   
    matrix.resize(matrix.size() + rowsNum, temp);

}

inline
double& Normal_matrix::at(cu_int row, cu_int col)
{

    return matrix.at(row).at(col);

}

inline
double Normal_matrix::at(cu_int row, cu_int col) const
{

    return matrix.at(row).at(col);

}

inline
const Normal_matrix operator+
(const Normal_matrix& fst, const Normal_matrix& snd)
{

    if( !fst.isCompatible(snd) )
        throw "You cannot do math operations with matrixes"
              "of different sizes";

    Normal_matrix operand1 = fst;
    for(auto i = 0; i < operand1.matrix.size(); i++)
        for(auto j = 0; j < operand1.matrix.at(0).size(); j++)
            operand1.at(i, j) += snd.at(i, j);

    return operand1;

}

inline
const Normal_matrix operator-
(const Normal_matrix& fst, const Normal_matrix& snd)
{

    if( !fst.isCompatible(snd) )
        throw "You cannot do math operations with matrix"
              "of different sizes";

    Normal_matrix operand1 = fst;
    for(auto i = 0; i < operand1.matrix.size(); i++)
        for(auto j = 0; j < operand1.matrix.at(0).size(); j++)
            operand1.at(i, j) -= snd.at(i, j);

    return operand1;

}

inline
void operator+=
(Normal_matrix& fst, const Normal_matrix& snd)
{

    fst = fst + snd;

}

inline
void operator-=
(Normal_matrix& fst, const Normal_matrix& snd)
{

    fst = fst - snd;

}

inline
const Normal_matrix operator*
(const Normal_matrix& fst, const Normal_matrix& snd)
{

    if( fst.matrix.size() == 0 )
    {
        if( snd.matrix.size() == 0)
            return fst;
        else
            throw "You cannot do math operations with matrix"
                  "of different sizes";
    }

    if( fst.matrix.at(0).size() != snd.matrix.size() )
        throw "You cannot do math operations with incompatible matrix";

    Normal_matrix result(snd.matrix.at(0).size(), fst.matrix.size());
    
    for(auto i = 0; i < fst.matrix.size(); i++)
        for(auto j = 0; j < snd.matrix.size(); j++)
            for(auto k = 0; k < snd.matrix.at(0).size(); k++)
            result.at(i, k) += fst.at(i, j) * snd.at(j, k); 

    return result;

}

inline
const Normal_matrix operator/
(const Normal_matrix& fst, const Normal_matrix& snd)
{

    if( !fst.isCompatible(snd) )
        throw "You cannot do math operations with matrix"
              "of different sizes";

    if( !snd.determinant() )
        throw "Determinant of the second matrix shouldn't be equal to zero";

    Normal_matrix tmp = snd;
    Normal_matrix minors = fst;
    for(auto i_rows = 0; i_rows < minors.matrix.size(); i_rows++)
        for(auto i_cols = 0; i_cols < minors.matrix.at(0).size(); i_cols++)
        {

            tmp.matrix.erase(tmp.matrix.begin()+i_rows);
            
            for(auto it = tmp.matrix.begin(); it != tmp.matrix.end(); ++it)
                (*it).erase( (*it).begin()+i_cols );
            
            minors.at(i_rows, i_cols) = tmp.determinant() *  pow( (-1), i_rows + i_cols );
            tmp = snd;

        }

    return fst * (minors.transpose() / snd.determinant());

}

inline
const Normal_matrix operator*
(const Normal_matrix& fst, long long num)
{

    Normal_matrix operand1 = fst;
    for(auto i = 0; i < operand1.matrix.size(); i++)
        for(auto j = 0; j < operand1.matrix.at(0).size(); j++)
            operand1.at(i, j) *= num;

    return operand1;

}

inline
const Normal_matrix operator/
(const Normal_matrix& fst, long long num)
{

    if(num == 0)
        throw "num shouldn't be zero";

    Normal_matrix operand1 = fst;
    for(auto i = 0; i < operand1.matrix.size(); i++)
        for(auto j = 0; j < operand1.matrix.at(0).size(); j++)
            operand1.at(i, j) /= num;

    return operand1;

}

inline
void operator*=
(Normal_matrix& fst, long long num)
{

    fst = fst * num;

}

inline
void operator/=
(Normal_matrix& fst, long long num)
{

    fst = fst / num;

}

inline
void operator*=
(Normal_matrix& fst, const Normal_matrix& snd)
{

    fst = fst * snd;

}

inline
void operator/=
(Normal_matrix& fst, const Normal_matrix& snd)
{

    fst = fst / snd;

}

inline
const Normal_matrix Normal_matrix::operator++
()
{

    Normal_matrix operand2(matrix.size(), matrix.at(0).size(), 1);
    *this = *this + operand2; 

    return *this;

}

inline
const Normal_matrix Normal_matrix::operator++
(int)
{

    Normal_matrix operand2(matrix.size(), matrix.at(0).size(), 1);
    *this = *this + operand2; 

    return *this - operand2;
    
}

inline
const Normal_matrix Normal_matrix::operator--
()
{

    Normal_matrix operand2(matrix.size(), matrix.at(0).size(), 1);
    *this = *this - operand2; 

    return *this;

}

inline
const Normal_matrix Normal_matrix::operator--
(int)
{

    Normal_matrix operand2(matrix.size(), matrix.at(0).size(), 1);
    *this = *this - operand2; 
    
    return *this + operand2;

}

inline
Normal_matrix& Normal_matrix::transpose
()
{

    Normal_matrix temp = *this;

    for(auto i = 0; i < matrix.size(); i++)
        for(auto j = 0; j < matrix.at(0).size(); j++)
            matrix.at(i).at(j) = temp.at(j, i);

    return *this;

}

inline
const double Normal_matrix::determinant
() const
{

    if(matrix.empty())
        throw "Matrix shouldn't be empty";

    if(matrix.size() != matrix.at(0).size())
        throw "Matrix should be square.";

    map<int, map<int, double>> temp;
    for(auto i = 0; i < matrix.size(); i++)
        for(auto j = 0; j < matrix.at(0).size(); j++)
            temp[i + 1][j + 1] = matrix.at(i).at(j);

    return Minor(temp, matrix.size(), matrix.at(0).size());

}
