#include "XMLCdata.h"

XMLCDATA::XMLCDATA()
{
	text = vector <string>{};
}

XMLCDATA::XMLCDATA(vector <string> _text) : text(_text)
{
}

void XMLCDATA::SetText(string str)
{
	this->text.push_back(str);
}

void XMLCDATA::TextCut()
{
	this->text.erase(text.end() - 1);
}

void XMLCDATA::CDATAtTextOut()
{
	for (int i = 0; i < text.size(); i++)
	{
		cout << text[i] << endl;
	}
}
