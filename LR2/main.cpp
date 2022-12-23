#include "Tree.h"
int main()
{
	Var vars;
	while (true)
	{
		LexemeAnalyzer analyze;
		Node* ExpressionTree = new Node;
		vector<Lexeme> postfix;
		LexemeBuffer lexemes;
		analyze.get_token(lexemes);
		vector<Lexeme> lexs = lexemes.getLexemes();
		if (lexs.size() > 0)
		{
			findMinus(lexs);
		}
		else { Error error(100); continue; }
		try
		{
			postfix = getPostfix(lexs);
		}
		catch (...)
		{
			Error error(102);
			continue;
		}
		try
		{
			ExpressionTree = buildTree(postfix);
		}
		catch (...)
		{
			Error error(102);
			continue;
		}
		try
		{
			if (ExpressionTree->lexeme.getType() == 61)
			{
				double result = calc(ExpressionTree->left, vars);
				vector<string> varNames;
				getVarNames(ExpressionTree->right, varNames);
				for (int i = 0; i < varNames.size(); i++)
				{
					vars.setValue(varNames[i], result);
				}
			}
			else cout << calc(ExpressionTree, vars) << endl;
		}
		catch (exception err)
		{
			cout << err.what() << endl;
			continue;
		}
	}
	return 0;
}