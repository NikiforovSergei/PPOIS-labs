#include "Header.h"

void line::read()
{
	while (true)
	{
		int i = 0;
		string str;
		getline(cin, str);
		if (str.find("Subsets") != -1)
		{
			int b = 8;
			if (str[8] == ' ')
				b++;
			set::FindSubsets(str.substr(b + 1, str.length() - b - 3));
			cout << "{}";
		}
		if (str[0] == '{')
		{
			string error = "";
			set::print(set::solve(str));
		}
		for (int i = 0; i < str.length(); i++)
		{
			if (isalpha(str[i]) && isupper(str[i]))
			{
				bool br = false;
				bool eq = false;
				string error = "";
				if (str.find("=") != -1) eq = true;
				if (str.find('{') != -1) br = true;

				if (eq && br)
				{
					SaveSet(str, error);

				}
				if (!eq && !br)
				{
					set::print(NamedSet::solve(str, error));
				}
				if (eq && !br)
				{
					NamedSolve(str, error);
				}
				if (error != "")
				{
					cout << "Error: " << error;
				}
				break;
			}
		}
		cout << endl;
	}
}