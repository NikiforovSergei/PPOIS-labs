#pragma once
#ifndef XMLCDATA_H
#define XMLCDATA_H

#include "instactions.h"

class XMLCDATA
{
public:
	XMLCDATA();
	XMLCDATA(vector <string> _text);
	void SetText(string str);
	void TextCut();
	void CDATAtTextOut();
private:
	vector <string> text;
};

#endif
