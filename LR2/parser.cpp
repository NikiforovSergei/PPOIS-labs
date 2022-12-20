#include "parser.h"

xml::Parser::Parser(std::ifstream* in_file)
{
	this->in_file = in_file;
	eof = false;
	document = new Document();
}


void xml::Parser::process()
{
	for (nextWord_inStream(); !eof; nextWord_inStream()) {
		checkNext() == '<' ? in_file->get(), processTag() : processText();
	}
}

void xml::Parser::nextWord_inStream()
{
	for (;;) {
		char next = checkNext();
		if (next == '\n') { in_file->get(); continue; };
		if (in_file->eof()) break;
		if (next != ' ') return;
		in_file->get();
	}
	eof = true;
}


xml::Tag* xml::Parser::make_tag(const std::string& content) const
{
	std::string left_sub, right_sub, value;
	size_t pos = content.find(" ");
	left_sub = content.substr(0, pos);
	std::vector<Attribute> attributes;
	std::string attributeName;
	std::string attributeValue = "";
	value = left_sub;
	right_sub = content.substr(pos + 1, content.size());
	for (;;) {
		pos = right_sub.find("=");
		if (pos != std::string::npos) pos = right_sub.find("=");
		else break;
		left_sub = right_sub.substr(0, pos);
		attributeName = left_sub;
		right_sub.erase(right_sub.begin());
		right_sub.erase(right_sub.end() - 1);
		right_sub = right_sub.substr(pos + 1, left_sub.size());

		if (attributeValue == right_sub) break;

		attributeValue = right_sub;

		Attribute attribute(attributeName, attributeValue);

		attributes.push_back(attribute);
		right_sub = content.substr(pos + 1, content.size());
	}
	return new Tag(value, attributes, 0);

}
int xml::Parser::checkNext() {
	return in_file->peek();
}

void xml::Parser::processTag()
{
	char next = checkNext();
	if (next == '?') {
		document->setFirstLine(getStringBefore('\n'));
	}
	else if (next == '/') {
		in_file->get();
		if (getStringBefore('>') == tags.top()->value) tags.pop();
	}
	else OpenTag();
}


void xml::Parser::OpenTag()
{
	std::string content = getStringBefore('>');
	Tag* tagElement = make_tag(content);
	if (document->root) {
		tagElement->parent = tags.top();
		tags.top()->children.push_back(tagElement);
		tags.push(tagElement);
	}
	else {
		document->root = tagElement;
		tags.push(tagElement);
	}
}


void xml::Parser::processText()
{
	std::string content = getStringBefore('<');
	Text* txt = new Text(content, tags.top(), content);
	tags.top()->children.push_back(txt);
	processTag();
}

std::string xml::Parser::getStringBefore(char ch)
{
	std::string text;
	getline(*in_file, text, ch);
	return text;
}