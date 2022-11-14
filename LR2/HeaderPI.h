#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "HeaderElement.h"
using namespace std;

	class PI : public Element
	{
	public:
		string value;
		void Output();
		PI();
		PI(string);
		friend ostream& operator<< (ostream& os, PI& pi);
	};
