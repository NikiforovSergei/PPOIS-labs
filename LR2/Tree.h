#pragma once
#include "Lexeme.h"
#include <stack>
struct Node
{
	Lexeme lexeme;
	Node* right = NULL;
	Node* left = NULL;
};
vector<string> getVarNames(Node*, vector<string>&);
Node* node(Node*, Node*, Lexeme&);
Node* buildTree(vector<Lexeme>&);
vector<Lexeme> getPostfix(vector<Lexeme>&);
double calc(Node*, Var&);