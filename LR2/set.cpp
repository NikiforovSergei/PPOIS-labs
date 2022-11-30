#include "Header.h"

void set::print(set* a)
{
	if (a == nullptr)
	{
		return;
	}
	cout << "{";
	for (int i = 0; i < a->elements.size(); i++)
	{
		cout << a->elements[i];
		if (i != a->elements.size() - 1 || a->subsets.size() != 0)
		{
			cout << ", ";
		}
	}

	for (int i = 0; i < a->subsets.size() != 0; i++)
	{
		print(a->subsets[i]);
		if (i != a->subsets.size() - 1)
			cout << ", ";
		else
		{
			cout << "}";
			return;
		}

	}
	if (a->subsets.size() == 0)
		cout << "}";
}

set* set::solve(string line)
{
	vector<set*> sets;
	char operation;

	for (int i = 0; i < line.length(); i++)
	{

		if (line[i] == '{')
		{
			int count = 1;
			set* a = MakeSet(line.substr(i));
			while (count > 0)
			{
				i++;
				if (line[i] == '{') count++;
				else if (line[i] == '}') count--;

				else if (!(isalpha(line[i]) or isdigit(line[i]) or line[i] == ',' or line[i] == ' '))
				{

					cout << "Error: set cannot contain any characters other than letters and numbers" << endl;
					return nullptr;
				}
			}
			if (a != nullptr)
				sets.push_back(a);
			else
				return nullptr;

		}
		else if (line[i] == '(')
		{
			int j = i + 1;
			int counter = 1;
			while (counter > 0)
			{

				if (line[j] == '(') counter++;
				else if (line[j] == ')') counter--;
				j++;
			}
			sets.push_back(solve(line.substr(j - i)));
			i += (j - i - 1);
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
	return sets[0];
}

set* set::MakeSet(string line)
{
	set* newset = new set;
	string temp;
	int i = 1;
	int count = 1;
	while (count > 0)
	{
		if (line[i] == '{')
		{
			count++;
			newset->subsets.push_back(MakeSet(line.substr(i)));
			while (line[i] != '}')
			{
				i++;
			}
		}
		if (line[i] == '}')
		{
			count--;
		}
		if (line[i] != ',' && line[i] != '}')
		{
			if (line[i] != ' ')
			{
				temp += line[i];
			}
		}

		if (line[i] == ',' && temp != "" || line[i] == '}' && temp != "")
		{
			newset->elements.push_back(temp);
			temp = "";
		}
		i++;
	}
	return newset;
}

set* set::Union(set* a, set* b)
{
	set* un = new set;

	for (int i = 0; i < a->elements.size(); i++)
	{
		un->elements.push_back(a->elements[i]);
	}

	for (int j = 0; j < b->elements.size(); j++)
	{
		bool ex = false;
		for (int i = 0; i < a->elements.size(); i++)
		{
			if (a->elements[i] == b->elements[j])
				ex = true;
		}
		if (!ex)
			un->elements.push_back(b->elements[j]);
	}

	for (int i = 0; i < a->subsets.size(); i++)
	{
		un->subsets.push_back(a->subsets[i]);
	}

	for (int j = 0; j < b->subsets.size(); j++)
	{
		bool ex = false;
		for (int i = 0; i < a->subsets.size(); i++)
		{
			if (compare(a->subsets[i], b->subsets[j]))
				ex = true;
		}
		if (!ex)
			un->subsets.push_back(b->subsets[j]);
	}

	return un;
}

set* set::Intersection(set* a, set* b)
{
	set* in = new set;

	for (int i = 0; i < a->elements.size(); i++)
	{
		for (int j = 0; j < b->elements.size(); j++)
		{
			if (a->elements[i] == b->elements[j])
				in->elements.push_back(b->elements[j]);
		}
	}

	for (int i = 0; i < a->subsets.size(); i++)
	{
		for (int j = 0; j < b->subsets.size(); j++)
		{
			if (compare(a->subsets[i], b->subsets[j]))
				in->subsets.push_back(b->subsets[j]);
		}
	}

	return in;
}

set* set::Difference(set* a, set* b)
{
	set* dif = new set;
	set* un = Union(a, b);
	set* in = Intersection(a, b);


	for (int i = 0; i < un->elements.size(); i++)
	{
		bool ex = false;
		for (int j = 0; j < in->elements.size(); j++)
		{
			if (un->elements[i] == in->elements[j])
				ex = true;
		}
		if (!ex)
			dif->elements.push_back(un->elements[i]);
	}

	for (int i = 0; i < un->subsets.size(); i++)
	{
		bool ex = false;
		for (int j = 0; j < in->subsets.size(); j++)
		{
			if (compare(un->subsets[i], in->subsets[j]))
				ex = true;
		}
		if (!ex)
			dif->subsets.push_back(un->subsets[i]);
	}

	return dif;
}

bool set::compare(set* a, set* b)
{
	sort(a->elements.begin(), a->elements.end());
	sort(b->elements.begin(), b->elements.end());
	if (a->elements != b->elements)
		return false;
	if (a->subsets.size() != b->subsets.size())
		return false;
	for (int i = 0; i < b->subsets.size(); i++)
	{
		for (int j = 0; j < a->subsets.size(); j++)
		{
			if (!set::compare(a->subsets[j], b->subsets[i]))
				return false;
			else
				return true;
		}
	}
	return true;
}

void set::FindSubsets(string line)
{
	int i = 0;
	line += " ";
	vector<string> el;
	string t = "";
	while (i < line.length())
	{
		if (line[i] == '{')
		{
			int count = 1;
			while (count > 1)
			{
				t += line[i];
				if (line[i] == '}')
				{
					count--;
				}
				i++;
			}
			break;
		}
		else if (line[i] != ' ' && line[i] != ',')
		{
			t += line[i];
		}
		else if (t != "")
		{
			el.push_back(t);
			t = "";
		}
		i++;
	}

	cout << "{";
	for (i = 0; i < el.size() - 1; i++)
	{
		cout << el[i] << ", ";
	}
	cout << el[el.size() - 1] << "} ";

	if (el.size() > 1)
	{
		for (i = 0; i < el.size(); i++)
		{
			string line2 = "";
			int count = 0;
			for (int j = 0; j < el.size(); j++)
			{
				if (j != i)
				{
					line2 += el[j];
					count++;
					if (count < el.size() - 1)
					{
						line2 += ", ";
					}
				}
			}
			FindSubsets(line2);
		}
	}
}