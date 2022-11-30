#include "Header.h"

void NamedSet::SaveSet(string line, string& error)
{
	int b = line.rfind('=') + 1;
	set* newset = set::solve(line.substr(b));
	if (newset == nullptr)
	{
		
	}

	for (int i = 0; i < line.length(); i++)
	{
		if (isalpha(line[i]) and isupper(line[i]))
		{
			if ((line[i + 1] == ' ' || line[i + 1] == '='))
			{
				cout << "Set " << line[i] << " was saved   ";
				NamedSets[line[i]] = newset;
			}
			else
			{
				error = "incorrect name";
			}
		}
	}
}

set* NamedSet::solve(string line, string& error)
{
	vector<set*> sets;
	char operation;
	bool eq = false;
	
	for (int i = 0; i < line.length(); i++)
	{
		if (isalpha(line[i]))
		{
			if (NamedSets.find(line[i]) == NamedSets.end())
			{
				error = "nonexistent variable";
				return nullptr;
			}
		}
	}

	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '(')
		{
			int j = i + 1;
			int counter = 1;
			while (counter != 0)
			{

				if (line[j] == '(') counter++;
				else if (line[j] == ')') counter--;
				j++;
			}
			sets.push_back(NamedSet::solve(line.substr(i + 1, j - i), error));
			i += (j - i - 1);
		}

		if (isalpha(line[i]))
		{
			if (NamedSets.find(line[i]) == NamedSets.end())
			{
				error = "nonexistent variable";
			}
			else
			{
				sets.push_back(NamedSets.find(line[i])->second);
			}
		}
		else if (line[i] != ' ')
		{
			operation = line[i];
		}

		if (sets.size() == 2)
		{
			set* result;
			if (operation == '+')
			{
				result = Union(sets[0], sets[1]);
				sets = {};
				sets.push_back(result);
			}
			else if (operation == '*')
			{
				result = Intersection(sets[0], sets[1]);
				sets = {};
				sets.push_back(result);
			}
			else if (operation == '-')
			{
				result = Difference(sets[0], sets[1]);
				sets = {};
				sets.push_back(result);
			}
		}
	}
	if (error == "")
		return sets[0];
	else
		return nullptr;
}

void NamedSet::NamedSolve(string line, string& error)
{
	set* newset = solve(line.substr(line.rfind('=') + 1), error);
	vector<char> names;

	for (int i = 0; i < line.rfind("="); i++)
	{
		if (line[i] != ' ' && line[i] != '=' && !isalpha(line[i]))
		{
			error = "incorrect expression";
		}
	}
	if (error == "")
	{
		for (int i = 0; i < line.rfind("="); i++)
		{
			if (isalpha(line[i]))
			{
				NamedSets[line[i]] = newset;
			}
		}
	}
	set::print(newset);
}
