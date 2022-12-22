#pragma once
#include <string>
#include "element.h"
namespace xml
{
	class Document
	{
		std::string first_line;
	public:
		Document();
		void setFirstLine(std::string line);
		Tag* root;
	};

}