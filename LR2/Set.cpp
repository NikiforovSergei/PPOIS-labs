#include "Header.h"

void Set::set_indtf(string _indtf) {
	indtf = _indtf;
}

Set::Set() {

}

Set::~Set() {
	clear();
}

void Set::Add_subset(Set _subset) {
	subsets.push_back(_subset);
}

void Set::Add_element(string _element) {
	elements.push_back(_element);
}

void Set::clear() {
	indtf.clear();
	elements.clear();
	subsets.clear();
	nums.clear();
}

bool Set::empty() {
	return (elements.empty() && nums.empty() && subsets.empty());
}

void Set::Add_num(int _num) {
	nums.push_back(_num);
}

Set Set::Unification(Set s1, Set s2) {
	Set s3;

	sort(s1.elements.begin(), s1.elements.end());
	sort(s2.elements.begin(), s2.elements.end());
	for (auto it1 : s1.elements)
		s3.elements.push_back(it1);

	for (auto it2 : s2.elements)
		if (find(s3.elements.begin(), s3.elements.end(), it2) == s3.elements.end())
			s3.elements.push_back(it2);

	sort(s1.nums.begin(), s1.nums.end());
	sort(s2.nums.begin(), s2.nums.end());
	for (auto it1 : s1.nums)
		s3.nums.push_back(it1);

	for (auto it2 : s2.nums)
		if (find(s3.nums.begin(), s3.nums.end(), it2) == s3.nums.end())
			s3.nums.push_back(it2);

	//sort(s1.subsets.begin(), s1.subsets.end());
	//sort(s2.subsets.begin(), s2.subsets.end());
	for (auto it1 : s1.subsets)
		s3.subsets.push_back(it1);

	for (auto it2 : s2.subsets) {
		bool is_alright_here = false;

		for (auto it3 : s3.subsets)
			if (it2.indtf == it3.indtf) {
				is_alright_here = true;
				break;
			}
		if (!is_alright_here) s3.subsets.push_back(it2);
	}
	s3.build_new_indtf();
	return s3;
}

Set Set::Intersection(Set s1, Set s2) {
	Set s3;

	for (auto it1 : s1.elements)
		for (auto it2 : s2.elements)
			if (it1 == it2) s3.elements.push_back(it1);

	for (auto it1 : s1.nums)
		for (auto it2 : s2.nums)
			if (it1 == it2) s3.nums.push_back(it1);

	for (auto it1 : s1.subsets)
		for (auto it2 : s2.subsets)
			if (it1.indtf == it2.indtf) s3.subsets.push_back(it1);

	s3.build_new_indtf();
	return s3;

}

Set Set::Symmetric_difference(Set s1, Set s2) {
	Set Un_set = Unification(s1, s2);
	Set Inter_set = Intersection(s1, s2);
	
	if (!Un_set.elements.empty() && !Un_set.elements.empty())
	for (int i = 0; i < Inter_set.elements.size(); i++)
		for (int j = 0; j < Un_set.elements.size(); j++)
			if (Un_set.elements[j] == Inter_set.elements[i]) Un_set.elements.erase(Un_set.elements.begin() + j);

	if (!Un_set.nums.empty() && !Un_set.nums.empty())
	for (int i = 0; i < Inter_set.nums.size(); i++)
		for (int j = 0; j < Un_set.nums.size(); j++)
			if (Un_set.nums[j] == Inter_set.nums[i]) Un_set.nums.erase(Un_set.nums.begin() + j);

	if(!Un_set.subsets.empty() && !Un_set.subsets.empty())
	for(int i = 0; i<Inter_set.subsets.size(); i++)
		for(int j = 0; j < Un_set.subsets.size();j++)
			if (Un_set.subsets[j].indtf == Inter_set.subsets[i].indtf) { Un_set.subsets.erase(Un_set.subsets.begin() + i); i--; }


	Un_set.build_new_indtf();
	return Un_set;
}

vector<Set> Set::Assignment(Set _s1, Set _s2, vector<Set> _data) {
	Set result;

	for (int i = 0; i < _data.size(); i++)
		if (_data[i].indtf == _s1.indtf && _data[i].elements == _s1.elements &&  _data[i].nums == _s1.nums) _data.erase(_data.begin() + i);

	for (int i = 0; i < _data.size(); i++)
		if (_data[i].indtf == _s2.indtf && _data[i].elements == _s2.elements  && _data[i].nums == _s2.nums) _data.erase(_data.begin() + i);

	if (_s1.indtf.size() == 1 && _s2.indtf.size() != 1) {
		result.indtf = _s1.indtf;
		result.elements = _s2.elements;
		result.nums = _s2.nums;
		result.subsets = _s2.subsets;
		_data.push_back(result);
	}
	else if (_s1.indtf.size() != 1 && _s2.indtf.size() == 1) {
		result.indtf = _s2.indtf;
		result.elements = _s1.elements;
		result.nums = _s1.nums;
		result.subsets = _s1.subsets;
		_data.push_back(result);
	}
	else if (_s1.indtf.size() == 1 && _s2.indtf.size() == 1) {
		_data.push_back(_s1);
		_data.push_back(_s2);
	}

	return _data;

}

string Set::get_indtf() {
	return indtf;
}

void Set::build_new_indtf() {
	if (indtf.size() == 1 && indtf[0] >= 'A' && indtf[0] <= 'Z') return;
	string new_indtf = "{";
	for (auto it : nums) {
		new_indtf += it;
		new_indtf += ',';
	}
	for (auto it : elements) {
		new_indtf += it;
		new_indtf += ',';
	}
	for (auto it : subsets) {
		new_indtf += it.indtf;
		new_indtf += ',';
	}
	if(new_indtf.back() == ',') new_indtf.pop_back();
	new_indtf += '}';
	indtf = new_indtf;
}

void Set::print() {
	if (indtf.size() == 1) cout << indtf << " = ";
	cout << "{";
	for (auto it : nums) { 
		cout << it; 
		if (it != nums.back())
			cout << ", ";
		else if (it == nums.back() && (!elements.empty() || !subsets.empty()))
			cout << ", ";
	}
	for (auto it : elements) {
		cout << it;
		if (it != elements.back())
			cout << ", ";
		else if (it == elements.back() && !subsets.empty())
			cout << ", ";
	}
	for (int i = 0; i < subsets.size(); i++) {
		subsets[i].print();
		if (i != subsets.size() - 1) cout << ", ";
	}
	cout << "}";

}

vector<Set> Set::get_subsets() {
	return subsets;
}

vector<string> Set::get_elements() {
	return elements;
}