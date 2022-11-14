#include"HeaderComment.h"
#include<fstream>
#include<iostream>
Comment::Comment(std::string comment)
{
	this->comment = comment; 
}
ostream& operator<<(ostream& os, Comment comment)
{
	return os << comment.comment;
}
void Comment::Output()
{
	std::cout << this->comment << endl;
}
Comment::Comment()
{

}