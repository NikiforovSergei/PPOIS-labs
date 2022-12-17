#include"Header.h"

Solver::Solver() {

}

string Solver::To_post_form(string _str, vector<Set> _Sets) {
	string result;
	Sets = _Sets;

	for (int i = 0; i < _str.size(); i++) {
		vector<Set> temp;
		Set T;
		int begin;
		Input_Processing asd;
		switch (_str[i])
		{
		case('('):case('*'):
			stack_ops.push_back(_str[i]);
			break;

		case('+'):
			if (stack_ops.empty()) stack_ops.push_back(_str[i]);
			else if (stack_ops.back() == '(' || stack_ops.back() == '-' || stack_ops.back() == '=') stack_ops.push_back(_str[i]);
			else {
				while (stack_ops.back() != '(' || stack_ops.back() != '-' || stack_ops.back() != '=' || !stack_ops.empty()) {
					result.push_back(stack_ops.back());
					stack_ops.pop_back();
					if (stack_ops.empty()) break;
				}
				stack_ops.push_back(_str[i]);
			}
			break;

		case('-'):
			if (stack_ops.empty()) stack_ops.push_back(_str[i]);
			else if (stack_ops.back() == '=' || stack_ops.back() == '(') stack_ops.push_back(_str[i]);
			else {
				while (stack_ops.back() != '=' || stack_ops.back() != '(' || !stack_ops.empty()) {
					result.push_back(stack_ops.back());
					stack_ops.pop_back();
					if (stack_ops.empty()) break;
				}
				stack_ops.push_back(_str[i]);
			}
			break;

		case('='):
			if (stack_ops.empty()) stack_ops.push_back(_str[i]);
			else if (stack_ops.back() == '(') stack_ops.push_back(_str[i]);
			else {
				while (stack_ops.back() != '(' || !stack_ops.empty()) {
					result.push_back(stack_ops.back());
					stack_ops.pop_back();
					if (stack_ops.empty()) break;
				}
				stack_ops.push_back(_str[i]);
			}
			break;

		case(')'):
			while (stack_ops.back() != '(') {
				result.push_back(stack_ops.back());
				stack_ops.pop_back();
			}
			stack_ops.pop_back();
			break;
		case('/'):
			i++;
			begin = i;
			while (_str[i] != '/') i++;
			asd.line = _str.substr(begin, i - begin); 
			temp = asd.Parse(asd.line);
			T = temp[0];
			T = set_boolean(T);
			Sets.push_back(T);
			_str.erase(begin - 1, i - begin + 2); _str.insert(begin - 1, T.get_indtf());
			i = begin - 1;
			result.push_back('{');
			break;

		default:
			result.push_back(_str[i]);
			break;
		}

	}
	while (!stack_ops.empty()) {
		result.push_back(stack_ops.back());
		stack_ops.pop_back();
	}
	return result;
}


vector<Set> Solver::Solve_post_form(string _post_form) {
	
	vector<string> stack_Sets;
	Operations ops;
	for (int i = 0; i < _post_form.size(); i++) {

		if (_post_form[i] == '{') {
			int counter = 0;
			string buffSet_indtf;
			do {
				buffSet_indtf.push_back(_post_form[i]);
				if (_post_form[i] == '{') counter++;
				else if (_post_form[i] == '}') counter--;

				if(counter != 0)
				i++;
				
			} while (counter != 0);

			stack_Sets.push_back(buffSet_indtf);

		}

		if (_post_form[i] >= 'A' && _post_form[i] <= 'Z') {
			string buffSet_indtf;
			buffSet_indtf.push_back(_post_form[i]);
			stack_Sets.push_back(buffSet_indtf);
		}

		if (_post_form[i] == '+' || _post_form[i] == '-' || _post_form[i] == '*' || _post_form[i] == '=') {
			string s1_indtf = stack_Sets.back(); stack_Sets.pop_back();
			string s2_indtf = stack_Sets.back(); stack_Sets.pop_back();

			Set s1, s2;
			for (auto set : Sets) {
				if (set.get_indtf() == s1_indtf) s1 = set;
				if (set.get_indtf() == s2_indtf) s2 = set;
			}
			Set s3;
			switch (_post_form[i])
			{
			case('+'):
				s3 = Unification(s1, s2);
				Sets.push_back(s3);
				stack_Sets.push_back(s3.get_indtf());
				break;
			case('*'):
				s3 = Intersection(s1, s2);
				Sets.push_back(s3);
				stack_Sets.push_back(s3.get_indtf());
				break;
			case('-'):
				s3 = Symmetric_difference(s1, s2);
				Sets.push_back(s3);
				stack_Sets.push_back(s3.get_indtf());
				break;
			case('='):
				Sets = Assignment(s1, s2, Sets);
				stack_Sets.push_back(Sets.back().get_indtf());
				break;
			}
			
		}

	}
	
	return Sets;

}