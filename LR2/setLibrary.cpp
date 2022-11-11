#include "setLibrary.h"


void Read_a_line::read_line()
{

	//написать size для A
	Saved_Set save_my_set;
	save_my_set.named_sets;
	while (true)
	{
		bool indicator = 0;
		string my_line;
		cout << endl;

		getline(cin, my_line);

		if (my_line.find("[") != -1) //проверка, вызывает ли пользователь подмножество 
		{
			cout << endl;
			Set::get_info(subset(my_line, save_my_set));
			continue;
		}

		if (my_line.find("size") != -1)  //проверка, вызывает ли пользователь метод size
		{

			size(my_line, save_my_set);
			continue;
		}

		for (int i = 0; i < my_line.length(); i++)
		{
			if (isalpha(my_line[i]) && isupper(my_line[i])) //проверка на работу с названным множеством
			{
				save_my_set.distr(my_line);
				indicator = true;
				break;
			}
		}



		if (!indicator)
		{
			Set::get_info(Sets_and_operations::solution(my_line));
		}
	}
}

void Saved_Set::save_sets(string line)
{
	int amount_of_eq = 0;
	int beg_str = line.rfind('=') + 1;
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
			if (line[i] == '=' or line[i] == ' ') { continue; }
			else if (isalpha(line[i]) and isupper(line[i]))
			{
				try
				{
					if (amount_of_eq > 0 and (line[i + 1] == ' ' or line[i + 1] == '='))
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
						catch (const char* str)
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
		catch (const char* str)
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
			catch (const char* exception)
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

	try
	{

		if (check_small && eq) {
			save_sets(my_str);
			return;
		}

		else if (!check_small && !eq) {
			get_info(operation_with_named_sets(my_str));
			return;
		}

		else if (!check_small && eq)
		{
			save_sets_work_with_named_sets(my_str);
			return;
		}

		throw "Invalid expression!";
	}
	catch (const char* str)
	{
		cout << "Error: " << str;
	}
}

void Set::get_info(Set* check)
{
	try
	{
		if (check == nullptr) throw "Can't be read";
	}
	catch (const char* str)
	{
		cout << str << endl;
		return;
	}
	cout << "{";
	for (int i = 0; i < check->elements.size(); i++)
	{
		cout << check->elements[i];
		if (i != check->elements.size() - 1 || check->subsets.size() != 0)
		{
			cout << ", ";
		}
	}

	for (int i = 0; i < check->subsets.size() != 0; i++)
	{
		get_info(check->subsets[i]);
		if (i != check->subsets.size() - 1) cout << ", ";
		else
		{
			cout << "}";
			return;
		}

	}
	if (check->subsets.size() == 0) cout << "}";
	return;
}

Set* Set::add_new_set_subset(Set* a) //копирует множество
{
	Set* Union = new Set;
	Union->elements = a->elements;
	for (int i = 0; i < a->subsets.size(); i++)
	{
		Union->subsets.push_back(add_new_set_subset(a->subsets[i]));
	}
	return Union;
}

bool Set::compare_subset(Set* a, Set* b) //сравнивает подмножества двух главных множеств
{
	sort(a->elements.begin(), a->elements.end());
	sort(b->elements.begin(), b->elements.end());
	if (a->elements != b->elements) return false;
	if (a->subsets.size() != b->subsets.size()) return false;
	for (int i = 0; i < b->subsets.size(); i++)
	{
		for (int j = 0; j < a->subsets.size(); j++)
		{
			if (!Set::compare_subset(a->subsets[j], b->subsets[i])) return false;
			else return true;
		}
	}
	return true;
}

Set* Set::sum(Set* a, Set* b)
{
	return Set::sum_private(Set::add_new_set_subset(a), b);
}

Set* Set::sum_private(Set* Union, Set* b) //Передается уже скопированное множество Union (оно же изначальное множество a)
{
	
	for (int i = 0; i < b->elements.size(); i++)
	{
		if (find(Union->elements.begin(), Union->elements.end(), b->elements[i]) == Union->elements.end())
		{
			Union->elements.push_back(b->elements[i]);
		}

	}

	for (int i = 0; i < b->subsets.size(); i++)
	{
		int counter = 0;
		for (int j = 0; j < Union->subsets.size(); j++)
		{
			if (Set::compare_subset(Union->subsets[j], b->subsets[i]))
			{
				break;
			}
			else { counter++; }

		}
		if (counter == Union->subsets.size())
		{
			Union->subsets.push_back(add_new_set_subset(b->subsets[i]));
		}

	}

	return Union;
}

Set* Set::composition(Set* a, Set* b)
{
	Set* intersection = new Set;
	for (int i = 0; i < a->elements.size(); i++)
	{
		auto same = find(b->elements.begin(), b->elements.end(), a->elements[i]);
		if (same != b->elements.end())
		{
			intersection->elements.push_back(*same);
		}
	}

	for (int i = 0; i < a->subsets.size(); i++)
	{
		for (int j = 0; j < b->subsets.size(); j++)
		{
			if (Set::compare_subset(a->subsets[i], b->subsets[j]))
			{
				intersection->subsets.push_back(Set::add_new_set_subset(a->subsets[i]));
				break;
			}
		}
	}

	return intersection;
}

Set* Set::simmetric_differences(Set* a, Set* b)
{
	Set* sim_difference = new Set;
	for (int i = 0; i < b->elements.size(); i++)
	{
		if (find(a->elements.begin(), a->elements.end(), b->elements[i]) == a->elements.end()) sim_difference->elements.push_back(b->elements[i]);
	}
	for (int i = 0; i < a->elements.size(); i++)
	{
		if (find(b->elements.begin(), b->elements.end(), a->elements[i]) == b->elements.end()) sim_difference->elements.push_back(a->elements[i]);
	}

	for (int i = 0; i < a->subsets.size(); i++)
	{
		int counter = 0;
		for (int j = 0; j < b->subsets.size(); j++)
		{
			if (Set::compare_subset(a->subsets[i], b->subsets[j]))
			{
				break;
			}
			else counter++;
		}
		if (counter == b->subsets.size()) sim_difference->subsets.push_back(Set::add_new_set_subset(a->subsets[i]));
	}

	for (int i = 0; i < b->subsets.size(); i++)
	{
		int counter = 0;
		for (int j = 0; j < a->subsets.size(); j++)
		{
			if (Set::compare_subset(b->subsets[i], a->subsets[j]))
			{
				break;
			}
			else counter++;
		}
		if (counter == a->subsets.size()) sim_difference->subsets.push_back(Set::add_new_set_subset(b->subsets[i]));
	}

	return sim_difference;
}

Set* Sets_and_operations::create_set(string set_str) //создает множество из строки
{
	Set* my_set = new Set;
	string temporary_string = "";
	for (int i = 1; i < set_str.length(); i++)
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
			my_set->subsets.push_back(create_set(set_str.substr(i, j - i + 1)));
			i = j;
		}
		else if (set_str[i] != ',' && set_str[i] != '}')
		{
			if (set_str[i] != ' ')
			{
				temporary_string += set_str[i];
			}
		}

		if (set_str[i] == ',' && temporary_string != "" || set_str[i] == '}' && temporary_string != "")
		{
			my_set->elements.push_back(temporary_string);
			temporary_string = "";
		}
		else continue;
	}
	return my_set;
}

Set* Sets_and_operations::find_Set(int& i, string line)
{
	int j = 1;
	int counter = 1;
	while (counter != 0)
	{
		if (line[j] == '{') counter++;
		else if (line[j] == '}') counter--;

		else if (!(isalpha(line[j]) or isdigit(line[j]) or line[j] == ',' or line[j] == ' '))
		{

			cout << "Error: set must not store any characters other than letters and numbers" << endl;
			return nullptr;
		}
		j++;
	}
	Set* a = create_set(line.substr(0, j + 1));
	i += j - 1;
	return a;
}

Set* Sets_and_operations::solution(string line)
{
	vector<Set*> sets_from_line;
	char operating;
	for (int i = 0; i < line.length(); i++)
	{

		if (line[i] == '{')		//Если встретили {, то это значит начало множества, ищем его границы
		{

			Set* a = find_Set(i, line.substr(i));
			if (a != nullptr)
				sets_from_line.push_back(a);
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
			sets_from_line.push_back(solution(line.substr(i + 1, j - i)));
			i += (j - i - 1);
		}
		else if (line[i] == '=')
		{
			try { throw "Wrong name or operation"; }
			catch (const char* str) {
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
			else if (operating == '*')
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

int Another_operations::size_for_set(Set* a)
{
	return (a->elements.size() + a->subsets.size());
}

void Another_operations::size(string str, Saved_Set a)
{
	while (true)
	{
		int a = str.find(" ");
		if (a != -1)
		{
			str.replace(a, 1, "");
		}
		else break;
	}

	try
	{
		int beg = str.find('('), end = str.rfind(')');
		if (str.substr(0, beg) != "size") throw "Function does not exist, did you mean size()?";
		if (str.substr(beg + 1, end - 1 - beg).length() == 1 and !isupper(str[5])) throw "wrong value in size()";
		if (str.substr(beg + 1, end - 1 - beg).length() != 1 and isupper(str[5])) throw "wrong value in size()";
	}
	catch (const char* str)
	{
		cout << "Error: " << str << endl;
		return;
	}

	if (isupper(str[5]))
	{
		try
		{
			if (a.named_sets.find(str[5]) != a.named_sets.end())
				cout << size_for_set(a.named_sets[str[5]]);
			else throw "non-existent variable! ";
		}
		catch (const char* str)
		{
			cout << "Error: " << str;
			return;
		}

	}
	else
	{
		try
		{

			Set* a = Sets_and_operations::create_set(str.substr(str.find("(") + 1, str.rfind(")") - str.find("(")));
			if (str[5] != '{') throw "wrong value in size()";
			cout << size_for_set(a);
		}
		catch (const char* str)
		{
			cout << "Error: " << str;
			return;
		}
	}
}

Set* Another_operations::subset(string my_str, Saved_Set a)
{
	//решить проблему с номером множества и подмножества
	Set* my_set = new Set;
	while (true)
	{
		int del = my_str.find(" ");
		if (del != -1)
		{
			my_str.replace(del, 1, "");
		}
		else break;
	}
	try
	{
		if (!isalpha(my_str[0]) or (isalpha(my_str[0]) and !isupper(my_str[0]))) throw "A substring can only be obtained from named sets";
		if (my_str[1] != '[') throw "invalid set name";
		if (a.named_sets.find(my_str[0]) == a.named_sets.end()) throw "non-existent variable! ";
		my_set = a.named_sets[my_str[0]];
	}
	catch (const char* str)
	{
		cout << "Error: " << str << endl;
		return nullptr;
	}
	int beg_Str = my_str.find('[') + 1;
	int end_Str = my_str.find(']') - beg_Str;

	int chis = stoi(my_str.substr(beg_Str, end_Str)) - 1;

	try
	{
		int sz = size_for_set(my_set);
		if (chis < 0 or chis >= sz) throw "beyond the set. ";

		if (my_set->elements.size() > chis)
		{
			Set* ret_Set = new Set;
			ret_Set->elements.push_back(my_set->elements[chis]);
			return ret_Set;
		}
		else
		{
			return  my_set->subsets[chis - my_set->elements.size()];
		}
	}
	catch (const char* str)
	{
		cout << "Error: " << str;
		return nullptr;
	}


}