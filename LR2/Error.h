#pragma once
#ifndef ERROR_H
#define ERROR_H

#include "instactions.h"
#include "Reg.h"

class Error
{
public:
	bool CheckData(vector<string>& mas);
private:
	bool CheckInstractions(vector<string>& mas);
	bool CheckAttribute(string str);
	bool CheckTag(string str);
	bool CheckRootTag(string str);
	Reg re;
};

#endif