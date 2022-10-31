#include "Header.h"

Set* Sets_and_operations::create_set(string set_str)//создает множество из строки
{
	Set* my_set = new Set;
	//cout << set_str;
	string temporary_string = "";
	for (int i = 1; i<set_str.length(); i++)
	{
		
		if (set_str[i] == '{')
		{
			int j = i;
			int counter = 1;
			while (counter != 0)
			{
				j++;
				if (set_str[j] == '{') counter++;
				else if (set_str[j] == '}') counter--;
			}
			my_set->subsets.push_back(create_set(set_str.substr(i, j - i+1)));
			i = j;
		}
		else if (set_str[i] != ',' && set_str[i] != '}')
		{
			if (set_str[i] != ' ')
			{
				temporary_string += set_str[i];
			}
		}
		
		if (set_str[i] == ',' && temporary_string!="" || set_str[i] == '}' && temporary_string != "")
		{
			my_set->elements.push_back(temporary_string);
			temporary_string = "";
		}
		else continue;
	}
	return my_set;
}

Set* Sets_and_operations::find_Set(int &i, string line)
{
	int j = 1;
	int counter = 1;
	while (counter != 0)
	{
		if (line[j] == '{') counter++;
		else if (line[j] == '}') counter--;
		
		else if (!(isalpha(line[j]) or isdigit(line[j]) or line[j]==','  or line[j]==' '))
		{

			cout << "Error: set must not store any characters other than letters and numbers" << endl;
			return nullptr;
		}
		j++;
	}
	Set* a = create_set(line.substr(0, j+1 ));
	i += j-1;
	return a;
}

Set* Sets_and_operations::solution(string line)
{
	vector<Set*> sets_from_line;
	char operating;
	for (int i = 0; i < line.length(); i++)
	{
		
		if (line[i] == '{') //Если встретили {, то это значит начало множества, ищем его гранцы
		{

			Set* a = find_Set(i, line.substr(i));
			if (a != nullptr)
				sets_from_line.push_back(a);
			//get_info(sets_from_line[0]);
			//cout << i;
			else return nullptr;

		}
		else if (line[i] == '(')
		{
			int j = i + 1;
			int counter = 1;
			while (counter != 0)
			{
				
				if (line[j] == '(') counter++;
				else if (line[j] == ')') counter--;
				j++;
			}
			sets_from_line.push_back(solution(line.substr(i+1, j - i)));
			i += (j-i-1);
		}
		else if (line[i] == '=')
		{
			try { throw "Wrong name or operation"; }
			catch(const char* str) {
				cout << "Error: " << str << endl;
				return nullptr;
			}
		}
		else if (line[i] != ' ')
		{

			operating = line[i];

		}

		if (sets_from_line.size() == 2)
		{
			Set* resulting_seet_after_operation;
			if (operating == '+')
			{
				resulting_seet_after_operation = sum(sets_from_line[0], sets_from_line[1]);
				sets_from_line = {};
				sets_from_line.push_back(resulting_seet_after_operation);
			}
			else if (operating=='*')
			{
				resulting_seet_after_operation = composition(sets_from_line[0], sets_from_line[1]);
				sets_from_line = {};
				sets_from_line.push_back(resulting_seet_after_operation);
			}
			else if (operating == '-')
			{
				resulting_seet_after_operation = simmetric_differences(sets_from_line[0], sets_from_line[1]);
				sets_from_line = {};
				sets_from_line.push_back(resulting_seet_after_operation);
			}
		}

	}
	return sets_from_line[0];
}