#include "Error.h"

bool Error::CheckData(vector<string>& mas)
{
	int root = 0;
	if (!CheckInstractions(mas))
	{
		cout << "" << endl;
		return false;
	}
	for (int i = 0; i < mas.size(); i++)
	{
		if (re.FindBeginTagWithCDATA(mas[i]) != "")
		{
			while (re.FindEndTagWithCDATA(mas[i]) == "")
			{
				i++;
			}
			i++;
		}
		if (!CheckTag(mas[i]))
		{
			cout << "ОШИБКА : тег в строке " << i + 1 << endl;
			return false;
		}
		if (CheckRootTag(mas[i]))
		{
			root++;
		}
	}
	if (root>1)
	{
		cout << "ОШИБКА : больше одного корневого тега" << endl;
		return false;
	}
	return true;
}

bool Error::CheckInstractions(vector<string>& mas)
{
	string instr, word;
	for (int i = 0; i < mas.size(); i++)
	{
		instr = re.FindInstruction(mas[i]);
		if (instr != "")
		{
			break;
		}
	}
	if (instr == "")
	{
		cout << "ОШИБКА : отсутствует инструкция обработки" << endl;
		return false;
	}
	istringstream ist(instr);
	while (ist >> word )
	{
		if ((re.FindAttibuteName(word) != "") && !(CheckAttribute(word)))
		{
			cout << "ОШИБКА : атрибут инструкции" << endl;
			return false;
		}
	}
	return true;
}

bool Error::CheckAttribute(string str)
{
	int firstChar = str.find(R"(=")");
	int secondChar = str.find(R"(")", firstChar + 2);
	return (firstChar != -1) && (secondChar != -1);
}

bool Error::CheckTag(string str)
{
	bool check = true;
	string word;
	int firstChar = str.find(R"(<)");
	int fifthChar = str.find(R"( />)", firstChar + 1);
	int secondChar;
	fifthChar != -1 ? secondChar = -1 : secondChar = str.find(R"(>)", firstChar + 1);
	int thirdChar = str.find(R"(</)", secondChar + 1);
	int fourthChar;
	thirdChar == -1 ? fourthChar = -1 : fourthChar = str.find(R"(>)", thirdChar + 2);
	if (re.FindTagWithAttriute(str) != "") {
		istringstream ist(str);
		while (ist >> word)
		{
			if ((re.FindAttibuteName(word) != "") && !(CheckAttribute(word)))
			{
				cout << "ОШИБКА : атрибут тега" << endl;
				return false;
			}
		}
	}
	if ((firstChar == -1) && (secondChar == -1) &&(thirdChar == -1) && (fourthChar == -1) && (fifthChar == -1)) {
		return true;
	}
	else if ((firstChar != -1) && (secondChar == -1) && (thirdChar == -1) && (fourthChar == -1) && (fifthChar != -1)){
		return true;
	}
	else if ((firstChar != -1) && (secondChar != -1) && (thirdChar == -1) && (fourthChar == -1) && (fifthChar == -1)) {
		return true;
	}
	else if ((firstChar == -1) && (secondChar == -1) && (thirdChar != -1) && (fourthChar != -1) && (fifthChar == -1)) {
		return true;
	}
	else if ((firstChar != -1) && (secondChar == -1) && (thirdChar == -1) && (fourthChar == -1) && (fifthChar != -1)) {
		return true;
	}
	else if ((firstChar != -1) && (secondChar != -1) && (thirdChar != -1) && (fourthChar != -1) && (fifthChar == -1)) {
		return true;
	}
	else { return false; }
}

bool Error::CheckRootTag(string str)
{
	int tab = str.find('\t');
	bool t = (tab == -1) && (re.FindEndTag(str) != "" || re.FindEmptyTag(str) != "");
	return (tab == -1) && (re.FindEndTag(str) != "" || re.FindEmptyTag(str) != "");
}
