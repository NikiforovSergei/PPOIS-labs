#pragma once
#ifndef XMLTAG_H
#define XMLTAG_H

#include "XMLTagAtttibute.h"
#include "instactions.h"
#include "XMLCdata.h"

class XMLEmptyTag
{
public:
	XMLEmptyTag();
	XMLEmptyTag(string _name);
	virtual string GetText();
	virtual string GetName();
	virtual void SetLeaf(XMLEmptyTag& leaf);
	virtual void SetText(string str);
protected:
	string name;
};

class XMLTag : public XMLEmptyTag
{
public:
	XMLTag();
	XMLTag(string _name, string _text);
	XMLTag(string _name);
	virtual ~XMLTag();
	string GetText() override;
	void SetLeaf(XMLEmptyTag& leaf) override;
	void SetText(string str) override;
protected:
	vector <XMLEmptyTag*> leafs;
	string text;
};

class XMLTagWithAttibute : public XMLTag
{
public:
	XMLTagWithAttibute();
	XMLTagWithAttibute(string _name, string _text, vector<XMLTagAttribute*> _attributes);
	XMLTagWithAttibute(string _name, vector<XMLTagAttribute*> _attributes);
	~XMLTagWithAttibute() override;
private:
	vector<XMLTagAttribute*> attributes;
};

class  XMLTagWithCDATA : public XMLEmptyTag
{
public:
	XMLTagWithCDATA();
	XMLTagWithCDATA(XMLCDATA& _CDATA);
	~XMLTagWithCDATA();
private:
	XMLCDATA* CDATA;
};

#endif