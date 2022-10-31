#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "multiset.h"
#include "parser.h"


using namespace std;
using namespace custom_multiset;

multiset::multiset(vector<string> set1) {

	sort(set1.begin(), set1.end());

	set = set1;

}

void multiset::set_container(vector<string> set1) {

	set = set1;

}

int multiset::get_coeff(string element) {

	bool is_one = true;
	string coef;

	for (char elem : element)
		if (!(elem >= '0' and elem <= '9'))
			return is_one ? 1 : stoi(coef);
		else {

			coef.push_back(elem);

			is_one = false;

		}

	return stoi(coef);

}

string multiset::get_elem(string element) {

	string given_element;

	for (char elem : element)
		if (!(elem >= '0' and elem <= '9') || given_element.size() > 0)
			given_element.push_back(elem);

	return given_element;

}
string multiset::get_set_string() {

	string output = "";

	output += "{ ";

	for (string element : set) {

		if (element == "%")
			output += "{}";

		if (element != *(set.end() - 1))
			output += element + ", ";
		else
			output += element + " ";

	}

	output += "}";

	return output;

}

bool multiset::operator == (multiset& obj) {

	return get_set_string() == obj.get_set_string();

}

bool multiset::operator != (multiset& obj) {

	return get_set_string() != obj.get_set_string();

}

ostream& multiset::operator << (ostream& os) {

	return os << get_set_string();

}

istream& multiset::operator >> (istream& in) {

	string output;

	in >> output;

	set = set_parser(output);

	return in;

}

vector<string> multiset::operator + (multiset const& obj) {

	vector<string> result_set;

	result_set = set_union(set, obj.set);

	return result_set;

}

vector<string> multiset::operator * (multiset const& obj) {

	vector<string> result_set;

	result_set = set_intersection(set, obj.set);

	return result_set;

}

vector<string> multiset::operator - (multiset const& obj) {

	vector<string> result_set;

	result_set = set_difference(set, obj.set);

	return result_set;

}

bool multiset::operator[](const string& obj) {

	return set_inclusion(obj);

}

vector<string> multiset::set_add(string new_element) {

	int new_element_coeff, pos = 0;
	string new_element_literal, elem_literal;
	multiset target(set);

	if (!target.set_inclusion(get_elem(new_element)))
		set.push_back(new_element);
	else {

		new_element_coeff = get_coeff(new_element);
		new_element_literal = get_elem(new_element);

		for (string element : set) {

			elem_literal = get_elem(element);

			if (elem_literal == new_element_literal) {

				set.erase(set.begin() + pos);
				set.insert(set.begin() + pos, to_string(get_coeff(element) + new_element_coeff) + elem_literal);
				cout << "The element has succesfully added to the multiset!";

				return set;

			}

			pos++;
		}
	}

	cout << "The element has succesfully added to the multiset!";

	return set;

}

vector<string> multiset::set_remove(string element_to_remove) {

	int pos = 0;
	string elem_literal;

	for (string elem : set) {

		elem_literal = get_elem(elem);

		if (elem_literal == element_to_remove) {

			set.erase(set.begin() + pos);
			cout << "The element has succesfully removed from the multiset!";

			return set;

		}

		pos++;

	}

	cout << "There's no match for passed element!";

	return set;

}

vector<string> multiset::set_union(vector<string> set_1, vector<string> set_2) {

	vector<string> result_set;
	string elem_1, elem_2, target;
	int max_elem, coef_1, coef_2;

	for (int i = 0; i < set_1.size(); i++)
		for (int k = 0; k < set_2.size(); k++) 
			if (get_elem(set_1[i]) == get_elem(set_2[k]))
				if (max(get_coeff(set_1[i]), get_coeff(set_2[i])) == get_coeff(set_1[i]))
					result_set.push_back(set_1[i]);
				else
					result_set.push_back(set_2[k]);

	for (int i = 0; i < set_1.size(); i++) {

		multiset res(result_set);

		if (!res.set_inclusion(get_elem(set_1[i])))
			result_set.push_back(set_1[i]);

	}

	for (int k = 0; k < set_2.size(); k++)
		for (int i = 0; i < set_1.size(); i++) {

			multiset res(result_set);

			if (!res.set_inclusion(get_elem(set_2[k]))) {
				if (get_elem(set_1[i]) == get_elem(set_2[i])) {
					if (max(get_coeff(set_1[i]), get_coeff(set_2[i])) == get_coeff(set_1[i])) {
						if (!res.set_inclusion(get_elem(set_1[i])))
							result_set.push_back(set_1[i]);
					}
					else
						if (!res.set_inclusion(get_elem(set_2[k])))
							result_set.push_back(set_2[k]);
				}
				else
					result_set.push_back(set_2[k]);
			}
			else
				if (!res.set_inclusion(get_elem(set_2[k])))
					result_set.push_back(set_2[k]);

		}


	return result_set;

}

vector<string> multiset::set_intersection(vector<string> set_1, vector<string> set_2) {

	vector<string> result_set;

	for (int i = 0; i < set_1.size(); i++)
		for (int k = 0; k < set_2.size(); k++) {

			multiset res(result_set);

			if (!res.set_inclusion(get_elem(set_1[i])))
				if (get_elem(set_1[i]) == get_elem(set_2[k]))
					if (min(get_coeff(set_1[i]), get_coeff(set_2[k])) == get_coeff(set_1[i]))
						result_set.push_back(set_1[i]);
					else
						result_set.push_back(set_2[k]);

		}

	return result_set;

}

vector<string> multiset::set_difference(vector<string> set_1, vector<string> set_2) {

	vector<string> result_set;
	multiset res2(set_2);
	string target, elem_1, elem_2;
	int coef_1, coef_2;

	for (int i = 0; i < set_1.size(); i++)
		for (int k = 0; k < set_2.size(); k++) {

			multiset res(result_set);

			if (!res.set_inclusion(get_elem(set_1[i])))
				if (get_elem(set_1[i]) == get_elem(set_2[i]))
					if (get_coeff(set_1[i]) > get_coeff(set_2[i]))
						result_set.push_back(to_string(get_coeff(set_1[i]) - get_coeff(set_2[i])) + get_elem(set_1[i]));

		}


	multiset res(result_set);

	for (string elem : set_1)
		if (!res.set_inclusion(get_elem(elem)) and !res2.set_inclusion(get_elem(elem)))
			result_set.push_back(elem);

	return result_set;

}

bool multiset::set_inclusion(string target) {

	string parsed_elem;

	for (string elem : set)
		if (get_elem(elem) == target)
			return true;

	return false;
}

int multiset::set_length() {

	return set.size();

}

bool multiset::is_empty() {

	if (set.empty())
		return true;

	return false;

}

void multiset::print() {

	cout << get_set_string();

}
