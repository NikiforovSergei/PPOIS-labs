/*!
* \file 
* This file containes main().	
*
* The header file header.h is attached to this file with the declaration of the Natural class and its methods.
*/
#include "header.h"
/*! Program entry point. 
\return If the program runs correctly, returns 0.
*/
int main()
{
	Natural a(1, 3);
	Natural b(1, 3), c = a / b;
	cout << c;
}