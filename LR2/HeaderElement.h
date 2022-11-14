#pragma once
#include <string>
#include<vector>
using namespace std;

	class Element
	{
	public:
		virtual void OutputClosingTag(int i);
		virtual void Output();
		Element();
		Element(Element*);
	};
