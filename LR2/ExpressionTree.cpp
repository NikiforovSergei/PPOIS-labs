#include "ExpressionTree.h"
vector<Lexeme> getPostfix(vector<Lexeme>& lexemes)
{
	stack <Lexeme> Stack;
	vector <Lexeme> postfix;
	for (int i = 0; i < lexemes.size(); i++)
	{
		if (lexemes[i].getType() == NUMBER || lexemes[i].getType() == NAME)
		{
			postfix.push_back(lexemes[i]);
		}
		else if (isfoo(lexemes[i].getType()))
		{
			postfix.push_back(lexemes[i]);
		}
		else if (isop(lexemes[i]))
		{
			if (!Stack.empty())
			{
				while (((Stack.top().getType() == 42 || Stack.top().getType() == 47) && (lexemes[i].getType() == 42 || lexemes[i].getType() == 47 || lexemes[i].getType() == 45 || lexemes[i].getType() == 43)) || ((Stack.top().getType() == 43 || Stack.top().getType() == 45) && (lexemes[i].getType() == 45 || lexemes[i].getType() == 43)) || lexemes[i].getType() == 61)
				{
					postfix.push_back(Stack.top());
					Stack.pop();
					if (Stack.empty())
					{
						break;
					}
				}
			}
			Stack.push(lexemes[i]);
		}
		else if (lexemes[i].getType() == 40)
		{
			Stack.push(lexemes[i]);
		}
		else if (lexemes[i].getType() == 41)
		{
			if (Stack.empty())
			{
				throw "Error";
			}
			while (Stack.top().getType() != 40)
			{
				postfix.push_back(Stack.top());
				Stack.pop();
			}
			Stack.pop();
		}
	}
	while (!Stack.empty())
	{
		postfix.push_back(Stack.top());
		Stack.pop();
	}
	return postfix;
}
Node* buildTree(vector <Lexeme>& postfix)
{
	stack <Node*> stack;
	Node* ExpressionTree = new Node;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i].getType() == NUMBER || postfix[i].getType() == NAME || isfoo(postfix[i].getType()))
		{
			Node* node = new Node;
			node->left = node->right = NULL;
			node->lexeme = postfix[i];
			stack.push(node);
		}
		else
		{
			Node* tree = new Node;
			if (stack.empty())
			{
				throw "Error";
			}
			tree->left = stack.top();
			stack.pop();
			if (stack.empty())
			{
				throw "Error";
			}
			tree->right = stack.top();
			stack.pop();
			tree = node(tree->left, tree->right, postfix[i]);
			stack.push(tree);
		}
	}
	ExpressionTree = stack.top();
	stack.pop();
	return ExpressionTree;
}
Node* node(Node* left, Node* right, Lexeme& lexeme)
{
	Node* node = new Node;
	node->left = left;
	node->right = right;
	node->lexeme = lexeme;
	return node;
}
double calc(Node* node, Var& vars)
{
	if (!node)
	{
		return 0;
	}
	if (!node->left && !node->right && node->lexeme.getType() == NAME)
		if (node->lexeme.getVar()[0] == '-')
		{
			node->lexeme.setSValue(node->lexeme.getVar().erase(0, 1));
			return -vars.getValue(node->lexeme.getVar());
		}
		else return vars.getValue(node->lexeme.getVar());
	if (!node->left && !node->right && node->lexeme.getType())
		return node->lexeme.getDValue(vars);
	double l_val = calc(node->left, vars);
	double r_val = calc(node->right, vars);
	if (node->lexeme.getType() == PLUS)
		return r_val + l_val;

	if (node->lexeme.getType() == MINUS)
		return r_val - l_val;

	if (node->lexeme.getType() == MUL)
		return r_val * l_val;
	if (l_val == 0)
	{
		throw exception("Divided by zero!");
	}
	return r_val / l_val;
}
vector<string> getVarNames(Node* node, vector<string>& varNames)
{
	if (!node)
	{
		return varNames;
	}
	if (node->lexeme.getType() == NAME)
	{
		varNames.push_back(node->lexeme.getVar());
	}
	getVarNames(node->right, varNames);
	getVarNames(node->left, varNames);
	return varNames;
}