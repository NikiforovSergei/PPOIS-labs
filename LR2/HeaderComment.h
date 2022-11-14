#pragma once
#include <string>
#include "HeaderElement.h"
#include<fstream>
using namespace std;

	class Comment : public Element
	{
	public:
		void Output();
		Comment();
		Comment(string comment);
		string comment;
		friend ostream& operator<<(ostream& os, Comment comment);
	};

