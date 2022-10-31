
#include "turingmashine.h"
#include<fstream>

void Turing::add_element(char value) {
	Node* buf = new Node;
	buf->value = value;
	if (!head) {
		tail = buf;
		head = buf;
	}
	else {
		tail->next = buf;
		buf->prev = tail;
		tail = buf;
	}
}

void Turing::show_element() {
	Node* buf = new Node;
	buf = head;
	while (buf != NULL) {
		std::cout << buf->value << " ";
		buf = buf->next;
	}
	std::cout << '\n';
}

void Turing::delete_element(Node* buf) {
	if (buf == NULL) {
		std::cerr << "Node can not be null\n";
	}
	if (buf == head && buf == tail)	head = tail = NULL;
	else if (buf == head) {
		head = buf->next;
		buf->next->prev = NULL;
	}
	else if (buf == tail) {
		tail = buf->prev;
		buf->prev->next = NULL;
	}
	else {
		buf->prev->next = buf->next;
		buf->next->prev = buf->prev;
	}
	delete buf;
}

void Turing::right_shift(Node*& buf) {
	buf = buf->next;
}

void Turing::left_shift(Node*& buf) {
	buf = buf->prev;
}

void Turing::change_element(Node*& buf, char value) {
	buf->value = value;
}

void Turing::run(std::vector<Rule>& rules, int size) {
	Rule r;
	for (int i = 0; i < size; ++i) {
		std::cin >> r.start
			>> r.end
			>> r.direction
			>> r.status;
		rules.push_back(r);
	}
}

void Turing::run_in_file(std::vector<Rule>& rules, int size, const char* path) {
	std::ifstream in(path, std::iostream::in);
	Rule r;
	for (int i = 0; i < size; ++i) {
		in >> r.start
			>> r.end
			>> r.direction
			>> r.status;
		rules.push_back(r);
	}
}

void Turing::analyze_rule(std::vector<Rule>& rules, int number, Turing turing, bool log) {
	Node* buf = new Node;
	Turing::breakpoint(number, buf, turing);
	int i = 0;
	while (buf) {
		if (buf->value == rules[i].start && rules[i].end != '-') {
			if (rules[i].direction == '>') {
				Turing::change_element(buf, rules[i].end);
				Turing::right_shift(buf);
			}
			else if (rules[i].direction == '<') {
				Turing::change_element(buf, rules[i].end);
				Turing::left_shift(buf);
			}
		}
		else if (buf->value == rules[i].start && rules[i].end == '-') {
			if (rules[i].direction == '>') {
				Turing::right_shift(buf);
				Turing::delete_element(buf->prev);
			}
			else if (rules[i].direction == '<') {
				Turing::left_shift(buf);
				Turing::delete_element(buf->prev);
			}
		}
		if (log)
			turing.show_element();
		i = rules[i].status - 1;
	}
}

void Turing::breakpoint(int number, Node*& buf, Turing turing) {
	buf = turing.head;
	for (int i = 0; i < number - 1; ++i) {
		buf = buf->next;
	}
}

void Turing::tape(int size) {
	char value;
	for (int i = 0; i < size; ++i) {
		std::cin >> value;
		Turing::add_element(value);
	}
}


void Turing::show_rules(std::vector<Rule>& rules, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << rules[i].start << ' '
			<< rules[i].end << ' '
			<< rules[i].direction << ' '
			<< rules[i].status << '\n';
	}
}

void Turing::change_rule(std::vector<Rule>& rules, int change) {
	change = change - 1;
	std::cin >> rules[change].start
		>> rules[change].end
		>> rules[change].direction
		>> rules[change].status;
}

void Turing::delete_rule(std::vector<Rule>& rules, int number) {
	rules.erase(rules.begin() + (number - 1));

}
