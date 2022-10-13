#include "Reg.h"

string Reg::FindBeginTag(string str)
{
	smatch answer;
	regex_search(str, answer, BeginTag_re);
	return answer[1];
}

string Reg::FindEndTag(string str)
{
	smatch answer;
	regex_search(str, answer, EndTag_re);
	return answer[1];
}

string Reg::FindEmptyTag(string str)
{
	smatch answer;
	regex_search(str, answer, EmptyTag_re);
	return answer[1];
}

string Reg::FindTagWithAttriute(string str)
{
	smatch answer;
	regex_search(str, answer, BeginTagWithAttibute_re);
	return answer[1];
}

string Reg::FindText(string str)
{
	smatch answer;
	regex_search(str, answer, Text_re);
	return answer[1];
}

string Reg::FindInstruction(string str)
{
	smatch answer;
	regex_search(str, answer, Instruction_re);
	return answer[1];
}

string Reg::FindComment(string str)
{
	smatch answer;
	regex_search(str, answer, Comment_re);
	return answer[1];
}

string Reg::FindAttibuteName(string str)
{
	smatch answer;
	regex_search(str, answer, AttibuteName_re);
	return answer[1];
}

string Reg::FindAttibuteValue(string str)
{
	smatch answer;
	regex_search(str, answer, AttibuteValue_re);
	return answer[1];
}

string Reg::FindBeginTagWithCDATA(string str)
{
	smatch answer;
	regex_search(str, answer, CDATAStart_re);
	return answer[0];
}

string Reg::FindEndTagWithCDATA(string str)
{
	smatch answer;
	regex_search(str, answer, CDATAEnd_re);
	return answer[0];
}

string Reg::FindTextTagWithCDATA(string str)
{
	smatch answer;
	regex_search(str, answer, CDATAText_re);
	return answer[1];
}

string Reg::DelTab(string str)
{
	string temp;
	regex_replace(back_inserter(temp), begin(str), end(str), Tab_re, "");
	return temp;
}

void Reg::DelComment(string& str)
{
	string temp;
	regex_replace(back_inserter(temp), begin(str), end(str), Comment_re, "");
	str = temp;
}
