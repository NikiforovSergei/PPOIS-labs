#pragma once
#include <iostream>

using namespace std;
/*!
	Main vector class
	\brief Present: public, private	
*/
class Vector
{
public:

/*!
	 
     \brief Creating initial values
	 \param[in,out] a the value of the end of the vector x
     \param[in,out] b the value of the end of the vector y
     \param[in,out] v the value of the end of the vector z
*/
	Vector(double a = 0, double b = 0, double v = 0); 
	
/*!
     Overloaded operator +
	 \brief Used to work with vector + vector values
	 \param v To specify the values of the second vector
*/
	Vector operator +(Vector v);

/*!
	 Overloaded operator +=
	 \brief Reduction operation vector + vector
	 \param v To specify the values of the second vector
*/
	Vector operator +=(Vector v);

/*!
	 Overloaded operator -
	 \brief Used to work with vector - vector values
	 \param v To specify the values of the second vector
*/
	Vector operator -(Vector v);

/*!
	 Overloaded operator -=
	 \brief Reduction operation vector - vector
	 \param v To specify the values of the second vector
*/
	Vector operator -=(Vector v);

/*!
	 Overloaded operator *
	 \brief Used to work with vector * vector values
	 \param v To specify the values of the second vector
*/
	Vector operator *(Vector v);

/*!
	 Overloaded operator *=
	 \brief Reduction operation vector * vector
	 \param v To specify the values of the second vector
*/
	Vector operator *=(Vector v);

/*!
	 Overloaded operator * (on number)
	 \brief Used to work with vector * number
	 \param value To specify the values of the number
*/
	Vector operator *(double value);

/*!
	 Overloaded operator *= (on number)
	 \brief Reduction operation vector * number
	 \param value To specify the values of the number
*/
	Vector operator *=(double value);

/*!
	 Overloaded operator /
	 \brief Used to work with vector / vector
	 \param v To specify the values of the second vector
*/
	Vector operator /(Vector v);

/*!
	 Overloaded operator /=
	 \brief Reduction operation vector / vector
	 \param v To specify the values of the second vector
*/
	Vector operator /=(Vector v);

/*!
	 Overloaded operator ^
	 \brief Used to find the cosine between two vectors
	 \param v To specify the values of the second vector
*/
	double operator ^(Vector v);

/*!
	 Overloaded operator >
	 \brief Used to define a vector with a higher value
	 \param v To specify the values of the second vector
*/
	bool operator >(Vector v);

/*!
	 Overloaded operator >=
	 \brief Used to define a vector whose values are greater than or equal to
	 \param v To specify the values of the second vector
*/
	bool operator >=(Vector v);

/*!
	 Overloaded operator <
	 \brief Used to define a vector with a value less than
	 \param v To specify the values of the second vector
*/
	bool operator <(Vector & other);

/*!
	 Overloaded operator <=
	 \brief Used to define a vector whose values are less than or equal to
	 \param v To specify the values of the second vector
*/
	bool operator <=(Vector v);

/*!
	 Overloaded operator ==
	 \brief Used to find equal vectors
	 \param v To specify the values of the second vector
*/
	bool operator ==(Vector v);

/*!
	 Function length_v
	 \brief Used to find the length of a vector
	 \param[out] rez Returns the result of the length of the vector
*/
	double length_v(double rez = 0);

/*!
	 Function view_vector()
	 \brief Used to view the ends of a vector
*/
	void view_vector();

/*!
	 Function ret_x()
	 \brief Designed to use the x value outside of the class
	 \return x
*/
	double ret_x()
	{
		return x;
	}

/*!
	 Function ret_y()
	 \brief Designed to use the y value outside of the class
	 \return y
*/
	double ret_y()
	{
		return y;
	}

/*!
	 Function ret_z()
	 \brief Designed to use the z value outside of the class
	 \return z
*/
	double ret_z()
	{
		return z;
	}


private:
	double x, y, z;
};

/*!
	Additional class Ños
	\brief Present: public, private
*/

class Cos
{
public:
	/*!
		 Cos constructor
		 \brief Creating initial value
		 \param[in,out] s Cosine value
	*/
	Cos(double s = 1);

	/*!
		 Function prosmotr()
		 \brief Used to view the operation of finding the cosine
	*/    
	void prosmotrcos();

	/*!
		 Overloaded operator ==
		 \brief Used for tests. To compare a given number with the received
		 \param v To specify the values of the cosine
	*/
	bool operator ==(Cos v);

	/*!
		 Function ret_s()
		 \brief Designed to use the p value outside of the class
		 \return p
	*/
	double ret_s()
	{
		return p;
	}

private:
	double p;
};