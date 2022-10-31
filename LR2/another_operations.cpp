#include "Header.h"
int Another_operations::size_for_set(Set* a)
{
	return (a->elements.size() + a->subsets.size());
}

void Another_operations::size(string str, Saved_Set a)
{
	while (true)
	{
		int a=str.find(" ");
		if (a != -1)
		{
			str.replace(a, 1, "");
		}
		else break;
	}
	
	try
	{
		int beg = str.find('('), end = str.rfind(')');
		//cout << str.substr(0, beg) << " " << str.substr(beg+1, end-1);
		if (str.substr(0, beg) != "size") throw "Function does not exist, did you mean size()?";
		if (str.substr(beg + 1, end - 1-beg).length() == 1 and !isupper(str[5])) throw "wrong value in size()";
		if (str.substr(beg + 1, end - 1-beg).length() != 1 and isupper(str[5])) throw "wrong value in size()";
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
		catch (const char * str)
		{
			cout <<"Error: "<< str;
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
	int beg_Str = my_str.find('[')+1;
	int end_Str = my_str.find(']')-beg_Str;

	int chis=stoi(my_str.substr(beg_Str, end_Str))-1;

	try
	{
		int sz = size_for_set(my_set);
		if (chis<0 or chis>=sz) throw "beyond the set. ";

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