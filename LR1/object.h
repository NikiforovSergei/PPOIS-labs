#pragma once
#include <string>
using namespace std;
class RECT {
public:
	/// <summary>
	/// \brief constructor
	/// \details setting values of arguments
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	RECT(int x,int y,int x1,int y1);

	RECT();

	~RECT();
	/// <summary>
	/// \brief setting values of arguments
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	void define(int x, int y, int x1, int y1);
	/// <summary>
	/// \brief showing values of arguments
	/// </summary>
	void show_xy();
	/// <summary>
	/// \details creates an array of arguments and passes it at the output
	/// </summary>
	/// <returns></returns>
	int* get_xy();
	/// <summary>
	/// \brief changes all values of arguments
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void move(int x,int y);
	/// <summary>
	/// \brief changes values of 3 arguments
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void change_size(int x, int y);
	/// <summary>
	/// /brief increase by 1 all values of arguments
	/// </summary>
	/// <returns></returns>
	RECT& operator ++();

	RECT& operator ++(int v);
	/// <summary>
	/// \brief decrease by 1 all values of arguments
	/// </summary>
	/// <returns></returns>
	RECT& operator --();

	RECT& operator --(int v);
	/// <summary>
	/// find the union of 2 rectangles
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	RECT operator +(const RECT& other);
	/// <summary>
	/// find the intersection of 2 rectangles
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	RECT operator -(const RECT& other);

	RECT operator +=(const RECT& other);

	RECT operator -=(const RECT& other);
	
	void operator =(const RECT& other);

private:
	/// <summary>
	/// \brief variable for left top vertex
	/// </summary>
	int x;
	/// <summary>
	/// \brief varible for left top vertex
	/// </summary>
	int y;
	/// <summary>
	/// \brief variable for buttom right vertex
	/// </summary>
	int x1;
	/// <summary>
	/// \brief varieble for buttom tight vertex
	/// </summary>
	int y1;
	/// <summary>
	/// find the max element of 2 arguments
	/// </summary>
	/// <param name=""></param>{x right}
	/// <param name=""></param>{x left}
	/// <returns></returns>
	int max(int, int);
	/// <summary>
	/// \brief find the min element of 2 arguments
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	int min(int, int);
};