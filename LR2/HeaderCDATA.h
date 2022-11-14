#pragma once
#include <vector>
#include<string>
#include "HeaderElement.h"
#include<fstream>
using namespace std;


	class CDATA: public Element
	{
	public:
		void Output();
		string text;
		CDATA();
		CDATA(string);
		friend ostream& operator<< (ostream& os, CDATA& cdata);
	};
