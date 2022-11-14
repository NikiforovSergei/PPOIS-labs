#pragma once

#include <fstream>
#include <stack>
#include <iostream>
#include <string>
#include <tuple>

#include"document.h"

namespace xml {

	class Parser
	{
		std::ifstream* in_file;
		std::stack<Tag*> tags;
		bool eof;
		Tag* make_tag(const std::string& content) const;
		void nextWord_inStream();
		int checkNext();
		void OpenTag();
		void processTag();
		void processText();
		std::string getStringBefore(char);

	public:
		Parser(std::ifstream* file);
		void process();
		Document* document;

	};
	

}