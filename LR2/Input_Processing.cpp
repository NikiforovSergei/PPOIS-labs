#include "Header.h"
#include<vector>
using namespace std;

Input_Processing::Input_Processing() {

}

Input_Processing::Input_Processing(string _str) {
	line = _str;
	Ignore_space();
}

int Input_Processing::get_size_of_line() {
	return line.size();
}

void Input_Processing::Ignore_space() {
	string new_line;
	for (auto it : line) if (it != ' ') new_line.push_back(it);
	line = new_line;
}


bool Input_Processing::Syntax_check() {

	vector<string> stack;
	try {
		for (auto it : line) {
			if (it == '{') { stack.push_back("{"); }

			else if (it == '}')
				if (stack.empty() || stack.back() != "{") throw ERROR_THROW(3)
				else stack.pop_back();


			if (it == '(') { stack.push_back("("); }

			else if (it == ')')
				if (stack.empty() || stack.back() != "(") throw ERROR_THROW(3)
				else stack.pop_back();


			if (it == '+' || it == '*' || it == '-')
				if (stack.empty()) continue;
				else if (stack.back() == "{") throw ERROR_THROW(4)


			if (it == '=' && !stack.empty()) return false;

			if (it >= 'a' && it <= 'z' && (stack.empty() || stack.back() == "(")) if (it == 'o' || it == 'l') continue;
			else throw ERROR_THROW(5)
		}
	}
	catch (Error::ER error)
	{
		std::cout << error.message << '\n';
		return false;
	}

	try {
		for (int i = 0; i < line.size(); i++) {
			if (line.substr(i, 5) == "Bool(") {
				line.erase(i, 5); line.insert(i, "/");
				int begin = i + 1;
				while (line[i] != ')') i++;
				int end = i;
				line.erase(i, 1); line.insert(i, "/");
				if (!Is_only_one_bool_argument(line.substr(begin, end - begin))) {
					throw ERROR_THROW(1);
				}
			}

		}
	}
	catch (Error::ER error)
	{	
		std::cout << error.message << '\n';
		return false;
	}

	try {
		if (!line.empty()) {
			if ((!isalpha(line.back()) && line.back() != ')' && line.back() != '}' && line.back() != '/') || (!isalpha(line[0]) && line[0] != '(' && line[0] != '{' && line[0] != '/')) return false;
		}
		else throw ERROR_THROW(2);
	}
	catch (Error::ER error)
	{
		std::cout << error.message << '\n';
		return false;
	}
	
	

	for (int i = 0; i < line.size() - 1; i++) {

		if (!isalnum(line[i]) && !isalnum(line[i + 1])) {
			if (line[i] == ',' && line[i + 1] == '{') continue;
			else if (line[i] == '{' && (line[i + 1] == '}' || line[i + 1] == '{')) continue;
			else if ((line[i] == '*' || line[i] == '-' || line[i] == '+' || line[i] == '=') && (line[i + 1] == '{' || line[i + 1] == '(' || line[i + 1] == '/')) continue;
			else if ((line[i] == '}' || line[i] == ')' || line[i] == '/') && (line[i + 1] == '*' || line[i + 1] == '-' || line[i + 1] == '+' || line[i + 1] == '=' || line[i + 1] == ')')) continue;
			else if (line[i] == '}' && (line[i + 1] == ',' || line[i + 1] == '}' || line[i + 1] == ')')) continue;
			else if (line[i] == '(' && line[i + 1] == '{') continue;
			else if (line[i] == '/' && (line[i + 1] == '{' || line[i + 1] == '+' || line[i + 1] == '-' || line[i + 1] == '*' || line[i + 1] == ')')) continue;
			else if (line[i] == '}' && line[i + 1] == '/') continue;
			else return false;
		}
		
	}

	try {
		if (stack.empty()) return true;
		else throw ERROR_THROW(3)
	}
	catch (Error::ER error)
	{
		std::cout << error.message << '\n';
		return false;
	}


}


vector<Set> Input_Processing::Parse(string line) {
	vector<Set> Sets;
	Set temp;

	if(!line.empty())
	for (int i = 0; i < line.size(); i++) {
		
		if (line[i] >= 'a' && line[i] <= 'z') {
			string element;
			element.push_back(line[i]);
			temp.Add_element(element);
		}
		
		if (line[i] >= '0' && line[i] <= '9') {
			string num;
			while (line[i] != ',' && i < line.size()) {
				num.push_back(line[i]); i++;
			}

			temp.Add_num(stoi(num));

		}

		if (line[i] >= 'A' && line[i] <= 'Z') {
			string indtf;
			indtf.push_back(line[i]);
			if (line.size() == get_size_of_line()) {
					temp.set_indtf(indtf);
					Sets.push_back(temp);
					temp.clear();
			}
			else {
				Set subset;
				subset.set_indtf(indtf);
				temp.Add_subset(subset);
			}
		}

		if (line[i] == '{') {
			vector<string> stack;
			stack.push_back("{");
			int begin_of_set = i + 1; i++;
			while (!stack.empty()) {
				if (line[i] == '{') stack.push_back("{");
				else if (line[i] == '}') stack.pop_back();
				i++;
			}
			vector<Set> T;
			T = Parse(line.substr(begin_of_set, i - 1 - begin_of_set));
			T[0].set_indtf(line.substr(begin_of_set - 1, i - begin_of_set + 1));
			if (line.size() == get_size_of_line()) { temp = T[0]; Sets.push_back(temp); temp.clear(); }
			else temp.Add_subset(T[0]);
			
		}



	}
	else {
		Set empty_set;
		empty_set.set_indtf("{}");
		Sets.push_back(empty_set);
	}
	if (!temp.empty()) Sets.push_back(temp);
	return Sets;
}

bool Input_Processing::Is_only_one_bool_argument(string _str) {
	Input_Processing T(_str);
	vector<Set> temp;
	temp = T.Parse(T.line);
	
	if (temp.size() == 1) return true;
	else {
		throw ERROR_THROW(1);

	}
}