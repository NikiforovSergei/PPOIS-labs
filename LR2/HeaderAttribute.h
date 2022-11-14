#pragma once
#include <string>

#include "HeaderElement.h"
#include<fstream>
using namespace std;
	class Attribute: public Element
	{
	public:
		Attribute();
		void Output();
		string name;
		string value;
		Attribute(string);
		friend ostream& operator<< (ostream& os, Attribute& attridute);

	};
