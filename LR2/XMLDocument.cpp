#include "XMLDocument.h"

XMLDocument::XMLDocument()
{
	path = "";
	instructions = vector <XMLDocumentInstruction*>{};
	rootTag = nullptr;
	comments = vector <XMLComment*>{};
}

XMLDocument::XMLDocument(string _path, vector <XMLDocumentInstruction*>& _instructions, XMLTag& _rootTag, vector <XMLComment*>& _comments) : path(_path), instructions(_instructions), rootTag(&_rootTag), comments(_comments)
{
}

XMLDocument::~XMLDocument()
{
	for (int i = 0; i < comments.size(); i++)
	{
		delete comments[i];
	}
	for (int i = 0; i < instructions.size(); i++)
	{
		delete instructions[i];
	}
	delete rootTag;
}

void XMLDocument::SetPath(string path)
{
	this->path = path;
}

void XMLDocument::SetInstractions(string str)
{
	string word;
	istringstream ist(str);
	while (ist >> word)
	{
		if (re.FindAttibuteName(word) != "") 
		{ 
			instructions.push_back(new XMLDocumentInstruction(re.FindAttibuteName(word), re.FindAttibuteValue(word))); 
		}
	}
}

void XMLDocument::SetComment(string str, int num)
{
	smatch answer;
	regex_search(str, answer, re.Comment_re);
	if (answer[1]!="")
	{ 
		comments.push_back(new XMLComment(answer[1], num));
	}
}

void XMLDocument::SetRootTeg(string str)
{
	if (re.FindBeginTag(str)!="")
	{
		rootTag = new XMLTag(re.FindBeginTag(str));
		return;
	}
	else if (re.FindTagWithAttriute(str)!="")
	{
		string word;
		istringstream ist(str);
		vector<XMLTagAttribute*> temp;
		while (ist >> word)
		{
			if (re.FindAttibuteName(word) != "")
			{
				temp.push_back(new XMLTagAttribute(re.FindAttibuteName(word), re.FindAttibuteValue(word)));
			}
		}
		rootTag = new XMLTagWithAttibute(re.FindTagWithAttriute(str), temp);
		return;
	}
	else if (re.FindEmptyTag(str) != "")
	{
		rootTag = new XMLEmptyTag(re.FindEmptyTag(str));
		return;
	}
}

void XMLDocument::SetTeg(XMLEmptyTag& root, vector<string>& mas, int& begin, int end)
{
	for (begin; begin < end; )
	{
		string str = mas[begin];
		XMLEmptyTag* children;
		if (re.FindEndTag(str) == root.GetName())
		{
			begin++;
			return;
		}
		if (re.FindBeginTagWithCDATA(str) != "")
		{
			XMLCDATA* temp = new XMLCDATA;
			if (re.FindTextTagWithCDATA(str) != "")
			{
				temp->SetText(re.FindTextTagWithCDATA(str));
				temp->CDATAtTextOut();
				children = new XMLTagWithCDATA(*temp);
				root.SetLeaf(*children);
				begin++;
				continue;
			}
			while (re.FindEndTagWithCDATA(str) == "")
			{
				begin++;
				str = mas[begin];
				temp->SetText(str);
			}
			temp->TextCut();
			temp->CDATAtTextOut();
			children = new XMLTagWithCDATA(*temp);
			root.SetLeaf(*children);
			begin++;
			continue;
		}
		else if (re.FindBeginTag(str) != "")
		{
			if (re.FindText(str)!="")
			{
				children = new XMLTag(re.FindBeginTag(str), re.FindText(str));
				cout << re.DelTab(re.FindText(str)) << endl;
				begin++;
				root.SetLeaf(*children);
				continue;
			}
			children = new XMLTag(re.FindBeginTag(str));
			begin++;
			SetTeg(*children, mas, begin, end);
			root.SetLeaf(*children);
			continue;
		}
		else if (re.FindEmptyTag(str) != "")
		{
			children = new XMLEmptyTag(re.FindEmptyTag(str));
			root.SetLeaf(*children);
			begin++;
			continue;
		}
		else if (re.FindTagWithAttriute(str) != "")
		{
			string word;
			istringstream ist(str);
			vector<XMLTagAttribute*> temp;
			while (ist >> word)
			{
				if (re.FindAttibuteName(word) != "")
				{
					temp.push_back(new XMLTagAttribute(re.FindAttibuteName(word), re.FindAttibuteValue(word)));
				}
			}
			if (re.FindText(str) != "")
			{
				children = new XMLTagWithAttibute(re.FindTagWithAttriute(str), re.FindText(str), temp);
				cout << re.DelTab(re.FindText(str)) << endl;
				begin++;
				root.SetLeaf(*children);
				continue;
			}
			children = new XMLTagWithAttibute(re.FindBeginTag(str), temp);
			begin++;
			SetTeg(*children, mas, begin, end);
			root.SetLeaf(*children);
			continue;
		}
		
		root.SetText(str);
		cout << re.DelTab(str) << endl;
		begin++;
	}
}

vector<string> XMLDocument::SetData(string& path)
{
	ifstream data(path);
	vector<string> temp;
	if (!data.is_open())
	{
		cout << "Ошибка : файл не открыт" << endl;
		exit(0);
	}
	string str;
	int num = 0;
	while (getline(data, str))
	{
		this->SetComment(str, num);
		re.DelComment(str);
		temp.push_back(str); 
		num++;
	}
	data.close();
	if (!error.CheckData(temp))
	{
		exit(0);
	}
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] == "") {
			temp.erase(temp.begin() + i);
		}
	}
	return temp;
}

void XMLDocument::OutComments()
{
	for (int i = 0; i < comments.size(); i++)
	{
		comments[i]->OutComment();
	}
}

void XMLDocument::CreateDoc(string path)
{
	int begin = 2;
	vector<string> data = SetData(path);
	this->SetInstractions(data[0]);
	this->SetRootTeg(data[1]);
	this->SetTeg(*rootTag, data, begin, data.size());
	this->OutComments();
}

XMLComment::XMLComment()
{
	text = "";
	numberString = 0;
}

XMLComment::XMLComment(string _text, int _numberString):text(_text), numberString(_numberString)
{
}

void XMLComment::OutComment()
{
	cout << "Комментарий: " << this->text << " Номер строки: " << this->numberString + 1 << endl;
}

XMLDocumentInstruction::XMLDocumentInstruction()
{
	name = "";
	value = "";
}

XMLDocumentInstruction::XMLDocumentInstruction(string _name, string _value) : name(_name), value(_value)
{
}
