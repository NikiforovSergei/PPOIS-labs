#pragma once
#ifndef REG_H
#define REG_H

#include "instactions.h"

class Reg
{
public:
	regex BeginTag_re{ (R"(<([A-Za-z0-9-]*?)>)") };
	regex Text_re{ (R"(>(.*?)<)") };
	regex EndTag_re{ (R"(</([A-Za-z0-9-]*?)>)") };
	regex BeginTagWithAttibute_re{ (R"(\<(.*?)\s)") };
	regex Attibute_re{ (R"(\s(.*?)>|\s(.*?)\s)") };
	regex AttibuteName_re{ (R"((.*?)=)") };
	regex AttibuteValue_re{ R"(\"(.*?)\")" };
	regex EmptyTag_re{ (R"(<(.*?) />)") };
	regex Instruction_re{ (R"(<\?xml(.*?)\?>)") };
	regex Comment_re{ (R"(<!-{2}\s(.*?)\s-{2}>)") };
	regex CDATAStart_re{ (R"(<!\[CDATA\[)") };
	regex CDATAEnd_re{ (R"(\]\]>)") };
	regex CDATAText_re{ (R"(<!\[CDATA\[(.*?)\]\]>)") };
	regex Tab_re{ (R"(\t)") };
	string FindBeginTag(string str);
	string FindEndTag(string str);
	string FindEmptyTag(string str);
	string FindTagWithAttriute(string str);
	string FindText(string str);
	string FindInstruction(string str);
	string FindComment(string str);
	string FindAttibuteName(string str);
	string FindAttibuteValue(string str);
	string FindBeginTagWithCDATA(string str);
	string FindEndTagWithCDATA(string str);
	string FindTextTagWithCDATA(string str);
	string DelTab(string str);
	void DelComment(string& str);
};

#endif
