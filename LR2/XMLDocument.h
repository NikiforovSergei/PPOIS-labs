#pragma once
#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H

#include "XMLTag.h"
#include "Reg.h"
#include "Error.h"

class XMLComment;
class XMLDocument;
class XMLDocumentInstruction;

class XMLDocument
{
public:
	XMLDocument();
	XMLDocument(string _path, vector <XMLDocumentInstruction*>& _instructions, XMLTag& _rootTag, vector <XMLComment*>& _comments);
	~XMLDocument();

	void CreateDoc(string pathIn);

private:
	void SetPath(string path);
	void SetInstractions(string str);
	void SetComment(string str, int num);
	void SetRootTeg(string str);
	void SetTeg(XMLEmptyTag& root, vector<string>& mas, int& begin, int end);
	vector<string> SetData(string& path);
	void OutComments();
	string path;
	vector <XMLDocumentInstruction*> instructions;
	XMLEmptyTag* rootTag;
	vector <XMLComment*> comments;
	Reg re;
	Error error;
};

class  XMLDocumentInstruction
{
public:
	XMLDocumentInstruction();
	XMLDocumentInstruction(string _name, string _value);
private:
	string name;
	string value;
};

class XMLComment
{
public:
	XMLComment();
	XMLComment(string _text, int _numberString);
	void OutComment();
private:
	string text;
	int numberString;
};

#endif