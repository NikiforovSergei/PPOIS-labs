#include "HeaderCDATA.h"
#include<fstream>
#include<iostream>
CDATA::CDATA()
{

}
CDATA::CDATA(string text)
{
	this->text = text;
}
ostream& operator<< (ostream& os, CDATA& cdata)
{
	return os << cdata.text;
}
void CDATA::Output()
{
	std::cout << this->text << endl;
}
