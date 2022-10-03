#include <iostream>
#include <fstream>
#include <Windows.h>

#include "XmlReader.h"
#include "XmlPrinter.h"

int main()
{
	using namespace XML;
	std::ifstream xmlFile;
	xmlFile.open("Input.xml");
	std::ofstream txtFile;
	txtFile.open("Output.txt");
	XmlReader reader(&xmlFile);
	reader.ReadAndDissasemble();
	XmlPrinter printer(reader.document, &txtFile);
	printer.Print();
	return 0;
}
