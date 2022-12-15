#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";
class Tree
{
private:
	Tree* node;
	Tree* left;
	Tree* right;
	string engWord, rusWord;
public:
	void setNode(Tree* node); 
	Tree* addNode(Tree* node, string& engWord, string& rusWord); 
	void clearTree(Tree* node); 
	void Print(Tree const* node, std::string const& rpref = "", std::string const& cpref = "", std::string const& lpref = "") 
	{
		if (!node) return;
		if (node->right)
			Print(node->right, rpref + "  ", rpref + ch_ddia_hor, rpref + ch_ver_spa);
		std::cout << cpref << node->engWord << '(' << node->rusWord << ')' << std::endl;
		if (node->left)
			Print(node->left, lpref + ch_ver_spa, lpref + ch_udia_hor, lpref + "  ");
	}
	Tree* Delete(Tree* node, string engWord); 
	void getNumber(Tree* node, int& number); 
	void getTranslate(Tree* node, string& engWord, string& rusWord);
	void changeTranslate(Tree* node, string& engWord, string& rusWord); 
	Tree* inputDictionary(Tree* node, string filename); 
};
class dictionary
{
public:
	Tree* node;
	dictionary()
	{
		node = NULL;
	}
	dictionary& operator+=(pair<string, string> words) //!overload operator for adding words
	{
		node = node->addNode(node, words.first, words.second);
		return *this;
	}
	dictionary& operator-=(string engWord) //!overload operator for deleting words
	{
		node = node->Delete(node, engWord);
		return *this;
	}
	string operator[](string engWord)//!overload operator for word translation search
	{
		string rusWord = "";
		node->getTranslate(node, engWord, rusWord);
		return rusWord;
	}
	void operator[](pair<string, string> words)//!overload operator for changing the translation of a word
	{
		node->changeTranslate(node, words.first, words.second);
	}
};
