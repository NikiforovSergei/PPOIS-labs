#include "Comment.h"

XML::Comment::Comment(std::string value)
{
	this->value = "<!" + value + ">";
}
