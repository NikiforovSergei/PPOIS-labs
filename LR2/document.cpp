#include "document.h"
#include <string>

xml::Document::Document()
{
	root = NULL;
	first_line = "<";	
}
void xml::Document::setFirstLine(std::string line) {
	first_line += line;
}
