#pragma once
#include "HeaderAttribute.h"
#include<vector>
#include<string>
#include "HeaderElement.h"
using namespace std;

	class Tag : public Element
	 {
	 public:
		string name;
		vector<Attribute>attributes;
		string value;
	
		Tag();
		Tag(string, vector<Attribute>, string);
		//void PrinteTag();
		void Output();
		void OutputClosingTag(int);
	};
