#pragma once
#include <string>
#include "element.h"

using namespace std;

namespace xml
{
	class Document
	{
		string first_line;
	public:
		Document();
		void setFirstLine(string line);
		Tag* root;
	};

}