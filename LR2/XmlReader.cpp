#include "XmlReader.h"

XML::XmlReader::XmlReader(std::ifstream *inputFile)
{
	this->inputFile = inputFile;
	currentFileRead = false;
	currentLine = 1;
	document = new Document();
}



void XML::XmlReader::ReadAndDissasemble()
{
	while (true)
	{
		GetToNextCharacter();
		if (currentFileRead)
		{
			return;
		}
		AnalyzeCharacters();
	}
}

void XML::XmlReader::GetToNextCharacter()
{
	while (true)
	{
		char nextCharacter = inputFile->peek();
		if (nextCharacter == '\n')
			currentLine++;
		else
		{
			if (inputFile->eof())
				currentFileRead = true;
			if (nextCharacter != ' ')
				return;
		}
		inputFile->get();
	}
	currentFileRead = true;
}

XML::TagElement* XML::XmlReader::ProcessLineToTagElement(std::string content) const
{
	char* nextToken = nullptr, * tokenValue, * subTokenValue, * nextSubToken = nullptr;
	tokenValue = strtok_s(&content[0], " ", &nextToken);
	int counter = 1; 
	std::string value;
	std::vector<Attribute> attributes;
	while (tokenValue != NULL)
	{
		if (counter == 1)
			value = tokenValue;
		else
		{
			subTokenValue = strtok_s(&tokenValue[0], "=", &nextSubToken);
			std::string attributeName = subTokenValue;
			subTokenValue = strtok_s(NULL, "=", &nextSubToken);
			std::string attributeValue = subTokenValue;
			attributes.push_back(*new Attribute(attributeName, attributeValue));
		}
		tokenValue = strtok_s(NULL, " ", &nextToken);
		counter++;
	}

	return new TagElement(value, attributes, nullptr);
}

void XML::XmlReader::AnalyzeNonTextElement()
{
	char nextCharacter = inputFile->peek();
	switch (nextCharacter)
	{
	case '?':
		AnalyzePI();
		break;
	case '!':
		AnalyzeComment();
		break;
	case '/':
		AnalyzeClosingTag();
		break;
	default:
		AnalyzeOpeningTag();
	}
}

void XML::XmlReader::AnalyzeCharacters()
{
	char nextCharacter = inputFile->peek();
	if (nextCharacter == '<')
	{
		inputFile->get();
		AnalyzeNonTextElement();
	}
	else
	{
		AnalyzeText();
	}
}

void XML::XmlReader::AnalyzePI()
{
	inputFile->get();
	document->PI = new ProcessingInstruction();
	document->PI->value = "<?" + ReturnStringUntilSymbol('?') + "?>";
	PushPointer();
}

void XML::XmlReader::AnalyzeOpeningTag()
{
	bool tagIsSelfClosing = false;
	std::string content = ReturnStringUntilSymbol('>');
	if (content.back() == '/')
	{
		tagIsSelfClosing = true;
		content.pop_back();
	}
	TagElement *tagElement = ProcessLineToTagElement(content);
	if (document->root == nullptr)
		document->root = tagElement;
	else
	{
		tagElement->parent = tagStack.top();
		tagStack.top()->children.push_back(tagElement);
	}
	if (!tagIsSelfClosing)
		tagStack.push(tagElement);
}

void XML::XmlReader::AnalyzeClosingTag()
{
	inputFile->get();
	std::string content = ReturnStringUntilSymbol('>');
	if (tagStack.empty())
		throw new std::exception("Met closing tag before any opening ones");
	if (content == tagStack.top()->value)
		tagStack.pop();
	else
		throw new std::exception("Closing tag didn't match the opening one");
}

void XML::XmlReader::AnalyzeText()
{
	TextElement *a = new TextElement(ReturnStringUntilSymbol('<'), tagStack.top());
	tagStack.top()->children.push_back(a);
	AnalyzeNonTextElement();
}

void XML::XmlReader::AnalyzeComment()
{
	inputFile->get();
	Comment *com = new Comment(ReturnStringUntilSymbol('>'));
	document->comments.push_back(*com);
}

void XML::XmlReader::PushPointer()
{
	ReturnStringUntilSymbol('>');
	if (inputFile->get() == '\n')
		currentLine++;
}

std::string XML::XmlReader::ReturnStringUntilSymbol(char symbol)
{
	std::string str;
	getline(*inputFile, str, symbol);
	currentLine += (int)count(str.begin(), str.end(), '\n');
	return str;
}
