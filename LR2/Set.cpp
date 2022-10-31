#include "Header.h"


void Set::get_info(Set* check)
{
	try
	{
		if (check== nullptr) throw "Can't be read";
	}
	catch(const char* str)
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
		//else if (i == check->elements.size() - 1 && check->subsets.size() == 0) cout << ")";
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
	//cout << "), ";
	return;
}

Set*  Set::add_new_set_subset(Set* a) //копирует множество
{
	Set* Union = new Set;
	Union->elements = a->elements;
	for (int i = 0; i < a->subsets.size(); i++)
	{
		Union->subsets.push_back(add_new_set_subset(a->subsets[i]));
	}
	return Union;
}

bool Set::compare_subset(Set* a, Set* b) //сравнивает подмножества двух главных множеств, 
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

Set* Set::sum_private(Set *Union, Set *b) //Передается уже скопированное множество Union (оно же изначальное множество a)
{
	//Set* Union = new Set;

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
				//cout << "simple: ";
				//cout << "\nRes: " << Set::compare_subset(Union->subsets[j], b->subsets[i]) << endl;
				break;
			}
			else { counter++; }
			
		}
		if (counter == Union->subsets.size())
		{
			//cout << "Add new element" << endl;
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
		if ( same!= b->elements.end())
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





