#include "HeaderPI.h"
#include<vector>
#include<fstream>
#include<iostream>
using namespace std;
PI::PI()
{

}
PI::PI(string pi)
{
	this->value = pi;
}
ostream& operator<< (ostream & os, PI& pi)
{
	return os << pi.value;
}
void PI::Output()
{
	cout << this->value << endl;
}