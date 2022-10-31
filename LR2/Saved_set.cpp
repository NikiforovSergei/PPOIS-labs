#include "Header.h"
void Saved_Set::save_sets(string line)
{
	int amount_of_eq = 0;
	int beg_str = line.rfind('=')+1;
	int end_str = line.length() - beg_str;
	string my_nonamed_set = line.substr(beg_str, end_str);
	Set* found_set = solution(my_nonamed_set);
	try
	{
		
		if (found_set == nullptr) throw "set must not store any characters other than letters";

	}
	catch (const char* str) {
		cout << "Error: " << str << endl;
		return;
	}
	

	

	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '=') amount_of_eq++;
	}
	
	for (int i = 0; i < beg_str - 1; i++)
	{
		try
		{
			if (line[i] == '=' or line[i]==' ') { continue; }
			else if (isalpha(line[i]) and isupper(line[i]))
				{
					try
					{
						if (amount_of_eq > 0 and ( line[i+1]==' ' or line[i+1]=='='))
						{

							try
							{
								if (named_sets.find(line[i]) == named_sets.end())
								{
									cout << "Set " << line[i] << " was saved" << endl;
									named_sets[line[i]] = found_set;
									amount_of_eq--;
								}
								else throw "a set with the same name already exists";
							}
							catch(const char* str)
							{
								cout << "Error: " << str << endl;
								return;
							}

									
						}
						else throw "incorrect name!";
					}
					catch (const char* str)
					{
						cout << "Error: " << str << endl;
						return;
					}
				}

			else throw "incorrect name!";
		}
		catch(const char* str)
		{
			cout << "Error: " << str << endl;
			return;
		}
		
	}
	Set::get_info(found_set);
}

Set* Saved_Set::operation_with_named_sets(string my_str)
{
	vector<Set*> names_of_sets;
	char operation;
	for (int i = 0; i < my_str.length(); i++)
	{
		if (my_str[i] == '(')
		{
			int j = i + 1;
			int counter = 1;
			while (counter != 0)
			{

				if (my_str[j] == '(') counter++;
				else if (my_str[j] == ')') counter--;
				j++;
			}
			names_of_sets.push_back(operation_with_named_sets(my_str.substr(i + 1, j - i)));
			i += (j - i - 1);
		}

		if (isalpha(my_str[i]))
		{
			char a;
			a = my_str[i];
			try {
				if (named_sets.find(a) == named_sets.end()) throw "non-existent variable! ";
				names_of_sets.push_back(named_sets.find(a)->second);
			}
			catch(const char* exception)
			{
				cout << "Error: " << exception << endl;
				return nullptr;
			}
				
		}
		else if (my_str[i] != ' ') operation = my_str[i];

		if (names_of_sets.size() >= 2)
		{
			if (operation == '+')
			{

				Set* element = sum(names_of_sets[0], names_of_sets[1]);
				names_of_sets = {};
				names_of_sets.push_back(element);

			}
			if (operation == '*')
			{

				Set* element = composition(names_of_sets[0], names_of_sets[1]);
				names_of_sets = {};
				names_of_sets.push_back(element);

			}
			if (operation == '-')
			{

				Set* element = simmetric_differences(names_of_sets[0], names_of_sets[1]);
				names_of_sets = {};
				names_of_sets.push_back(element);
			}
		}
	}
	return names_of_sets[0];
}

void Saved_Set::save_sets_work_with_named_sets(string my_str)
{
	Set* set_value = operation_with_named_sets(my_str.substr(my_str.rfind('=') + 1));
	vector<char> names;
	for (int i = 0; i < my_str.rfind("="); i++)
	{
		if (isalpha(my_str[i]))
		{
			named_sets[my_str[i]] = set_value;
			Set::get_info(set_value);
		}
		
	}
}

void Saved_Set::distr(string my_str)
{
	bool check_small = 0, eq = 0;
	if (my_str.find("=") != -1) eq = 1;
	if (my_str.find('{') != -1) check_small = 1;
	
	/*if (my_str.find("[") != -1)
	{
		Another_operations* a;
		get_info(a->subset(my_str));

	}*/
	try
	{

		if (check_small && eq) {
			save_sets(my_str);
			return;
		}

		else if (!check_small && !eq) {
			get_info(operation_with_named_sets(my_str)); 
			return; }

		else if (!check_small && eq)
		{
			save_sets_work_with_named_sets(my_str);
			return;
		}

		throw "Invalid expression!" ;
	}
	catch(const char* str)
	{
		cout << "Error: " << str;
	}
}


