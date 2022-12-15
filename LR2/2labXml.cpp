#include "XML.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

int main()
{
	XML test_XML;
	test_XML = test_XML.readXmlFromFile("input.txt");
	cout << test_XML;
}