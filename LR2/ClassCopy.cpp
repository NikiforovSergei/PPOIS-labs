#include "ClassCopy.h"

void Copy_Class::copy_class(std::ostream& out)
{
	out << "#include <iostream> \n";
	out << "#include <string>\n";
	out << "#include<conio.h>\n";


	out << "using namespace std;\n";

	out << "class Stack {\n";
	out << "private:\n";

	out << "class Node {\n";
	out << "public:\n";
	out << "		int var;\n";
	out << "		Node* next;\n";
	out << "	};\n";

	out << "	Node* head;\n";
	out << "	Node* tail;\n";

	out << "	public:\n";

	out << "	Stack() {\n";
	out << "		head = nullptr;\n";
	out << "		tail = nullptr;\n";
	out << "	}\n";

	out << "	~Stack() {\n";
	out << "		Node* node;\n";
	out << "		node = tail;\n";

	out << "		while (tail != nullptr) {\n"; //deletes all nodes
	out << "			node = tail;\n";
	out << "			tail = tail->next;\n";
	out << "			delete node;\n";
	out << "		}\n";
	out << "		head = nullptr;\n";
	out << "		tail = nullptr;\n";
	out << "	}\n";

	out << "	void del_el() {\n";// deletes head
	out << "		Node* node;\n";
	out << "		node = tail;\n";

	out << "		if (node == head) {\n";
	out << "			delete node;\n";
	out << "			head = nullptr;\n";
	out << "			tail = nullptr;\n";
	out << "		}\n";
	out << "		else {\n";
	out << "			while (node->next->next != nullptr) {\n";// finds pre-head, deletes head, makes head from pre-head
	out << "				node = node->next;\n";
	out << "			}\n";
	out << "			Node* del;\n";
	out << "			del = node->next;\n";
	out << "			head = node;\n";
	out << "			head->next = nullptr;\n";
	out << "			delete del;\n";
	out << "		}\n";

	out << "	}\n";

	out << "	void push(int num) {\n";// pushes integer number to stack
	out << "		Node* node = new Node;\n";
	out << "		node->var = num;\n";

	out << "		if (head == nullptr && tail == nullptr) {\n";
	out << "			head = node;\n";
	out << "			tail = node;\n";
	out << "			node->next = nullptr;\n";
	out << "		}\n";
	out << "		else {\n";
	out << "			node->next = tail;\n";
	out << "			tail = node;\n";
	out << "		}\n";
	out << "	}\n";

	out << "	int pop() {\n";
	out << "		int a;\n";
	out << "		a = head->var;\n";
	out << "		this->del_el();\n";
	out << "		return a;\n";
	out << "	}\n";


	out << "	void peek(int& num) {\n";// gives num head->var value
	out << "		num = head->var;\n";
	out << "	}\n";

	out << "	void dup() {\n";// puts head->var value to stack
	out << "		int num;\n";
	out << "		num = head->var;\n";
	out << "		this->push(num);\n";
	out << "	}\n";

	out << "	void add() {\n";
	out << "		int a, b;\n";
	out << "		a = head->var;\n";
	out << "		this->del_el();\n";
	out << "		b = head->var;\n";
	out << "		this->del_el();\n";

	out << "		this->push(a + b);\n";
	out << "	}\n";

	out << "	void sub() {\n";
	out << "		int a, b;\n";
	out << "		a = head->var;\n";
	out << "		this->del_el();\n";
	out << "		b = head->var;\n";
	out << "		this->del_el();\n";

	out << "		this->push(a - b);\n";
	out << "	}\n";

	out << "	void mul() {\n";
	out << "		int a, b;\n";
	out << "		a = head->var;\n";
	out << "		this->del_el();\n";
	out << "		b = head->var;\n";
	out << "		this->del_el();\n";

	out << "		this->push(a * b);\n";
	out << "	}\n";

	out << "	void div() {\n";
	out << "		int a, b;\n";
	out << "		a = head->var;\n";
	out << "		this->del_el();\n";
	out << "		b = head->var;\n";
	out << "		this->del_el();\n";

	out << "		this->push(a / b);\n";
	out << "	}\n";

	out << "	void print() {\n";
	out << "		Node* node;\n";
	out << "		node = tail;\n";
	out << "		printf(\"tail>>>  \");\n";

	out << "		while (node != nullptr) {\n";
	out << "			printf(\"%d%s\", node->var, \" \");\n";
	out << "			node = node->next;\n";
	out << "		}\n";

	out << "		printf(\" <<<head \\n\");\n";
	out << "	}\n";
	out << "};\n";
}

void Copy_Operators::copy_push(std::ostream& out, std::string num) {
	out << "	stack.push(" << num << ");\n";
}

void Copy_Operators::copy_peek(std::ostream& out, std::string num)
{
	out << "	stack.peek(" << num << ");\n";
}

void Copy_Operators::copy_dup(std::ostream& out)
{
	out << "	stack.dup();\n";
}

void Copy_Operators::copy_add(std::ostream& out)
{
	out << "	stack.add();\n";
}

void Copy_Operators::copy_sub(std::ostream& out)
{
	out << "	stack.sub();\n";
}

void Copy_Operators::copy_mul(std::ostream& out)
{
	out << "	stack.mul();\n";
}

void Copy_Operators::copy_div(std::ostream& out)
{
	out << "	stack.div();\n";
}

void Copy_Operators::copy_print(std::ostream& out)
{
	out << "	stack.print();\n";
}

