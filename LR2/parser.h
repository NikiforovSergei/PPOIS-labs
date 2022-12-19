#pragma once

#include <fstream>
#include <stack>
#include <iostream>
#include <string>
#include <tuple>

#include"document.h"
#include"element.h"

using namespace std;

namespace xml {

	class Parser
	{
		ifstream* in_file;
		stack<Tag*> tags;
		bool eof;
		Tag* make_tag(const string& content) const;
		void nextWord_inStream();
		int checkNext();
		void OpenTag();
		void processTag();
		void processText();
		string getStringBefore(char);
	public:
		Parser(ifstream* file);
		void process();
		Document* document;
	};
}