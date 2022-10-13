#pragma once
#ifndef XMLTAGATTRIBUTE_H
#define XMLTAGATTRIBUTE_H

#include "instactions.h"

class XMLTagAttribute
{
public:
	XMLTagAttribute(string _name, string _value);
private:
	string name;
	string value;
};

#endif