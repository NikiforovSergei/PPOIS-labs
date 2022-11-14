#include <iostream>
#include <fstream>
#include "../StaticLib/HeaderDoc.h"
#include<Windows.h>
#include "../StaticLib/HeaderTree.h"
using namespace std;
int main() 
{

	setlocale(LC_ALL, "Rus");
	ifstream fs;
	Document doc = Document();
	
	fs.open("./xmlFile.xml");
	doc.GetELement(fs);

}