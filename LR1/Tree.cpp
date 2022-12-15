#include "Tree.h"
void Tree::setNode(Tree* node)
{
	this->node = node;
}
/*!
	 \brief adding a vertex (word) to a tree (dictionary)
 */
Tree* Tree::addNode(Tree* node, string& engWord, string& rusWord)
{
	if (!node)
	{
		node = new Tree;
		node->engWord = engWord;
		node->rusWord = rusWord;
		node->left = node->right = NULL;
	}
	else if (node->engWord > engWord)
	{
		node->left = addNode(node->left, engWord, rusWord);
	}
	else
		node->right = addNode(node->right, engWord, rusWord);
	return node;
}
/*!
	 \brief clear tree
 */
void Tree::clearTree(Tree* node) {
	if (node) {
		clearTree(node->left);
		clearTree(node->right);
		delete node;
	}
}
/*!
	 \brief deleting a vertex (word) in a tree (dictionary)
 */
Tree* Tree::Delete(Tree* node, string engWord)
{
	if (!node)
		return node;
	else if (node->engWord == engWord)
	{
		Tree* tmp;
		if (!node->right)
			tmp = node->left;
		else {
			Tree* p = node->right;
			if (!p->left) {
				p->left = node->left;
				tmp = p;
			}
			else {
				Tree* pmin = p->left;
				while (pmin->left) {
					p = pmin;
					pmin = p->left;
				}
				p->left = pmin->right;
				pmin->left = node->left;
				pmin->right = node->right;
				tmp = pmin;
			}
		}
		delete node;
		return tmp;
	}
	else if (node->engWord > engWord)
		node->left = Delete(node->left, engWord);
	else
		node->right = Delete(node->right, engWord);
	return node;
}
/*!
	 \brief getting the number of vertices (words) in a tree (dictionary)
 */
void Tree::getNumber(Tree* node, int& number)
{
	if (node)
	{
		number++;
		getNumber(node->left, number);
		getNumber(node->right, number);
	}
}
/*!
	 \brief getting a translation of a word (searching for it)
 */
void Tree::getTranslate(Tree* node, string& engWord, string& rusWord)
{
	if (rusWord.length() == 0 && node)
	{
		if (node->engWord == engWord)
		{
			rusWord = node->rusWord;
		}
		getTranslate(node->left, engWord, rusWord);
		getTranslate(node->right, engWord, rusWord);
	}
	return;
}
/*!
	 \brief changing the translation of a word
 */
void Tree::changeTranslate(Tree* node, string& engWord, string& rusWord)
{
	if (node)
	{
		if (node->engWord == engWord)
		{
			node->rusWord = rusWord;
		}
		changeTranslate(node->left, engWord, rusWord);
		changeTranslate(node->right, engWord, rusWord);
	}
	return;
}
/*!
	 \brief writing a dictionary (tree) to a file
 */
Tree* Tree::inputDictionary(Tree* node, string filename)
{
	vector<string> engWord;
	vector<string> rusWord;
	int number = 0;
	ifstream input("data.txt");
	input >> number;
	for (int i = 0; i < number; i++)
	{
		string rus, eng;
		input >> eng >> rus;
		engWord.push_back(eng);
		rusWord.push_back(rus);
	}
	input.close();
	for (int i = 0; i < number; i++)
	{
		node = node->addNode(node, engWord[i], rusWord[i]);
	}
	return node;
}