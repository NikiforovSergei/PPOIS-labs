#include <iostream> 
#include <string>
#include<conio.h>
using namespace std;
class Stack {
private:
class Node {
public:
		int var;
		Node* next;
	};
	Node* head;
	Node* tail;
	public:
	Stack() {
		head = nullptr;
		tail = nullptr;
	}
	~Stack() {
		Node* node;
		node = tail;
		while (tail != nullptr) {
			node = tail;
			tail = tail->next;
			delete node;
		}
		head = nullptr;
		tail = nullptr;
	}
	void del_el() {
		Node* node;
		node = tail;
		if (node == head) {
			delete node;
			head = nullptr;
			tail = nullptr;
		}
		else {
			while (node->next->next != nullptr) {
				node = node->next;
			}
			Node* del;
			del = node->next;
			head = node;
			head->next = nullptr;
			delete del;
		}
	}
	void push(int num) {
		Node* node = new Node;
		node->var = num;
		if (head == nullptr && tail == nullptr) {
			head = node;
			tail = node;
			node->next = nullptr;
		}
		else {
			node->next = tail;
			tail = node;
		}
	}
	int pop() {
		int a;
		a = head->var;
		this->del_el();
		return a;
	}
	void peek(int& num) {
		num = head->var;
	}
	void dup() {
		int num;
		num = head->var;
		this->push(num);
	}
	void add() {
		int a, b;
		a = head->var;
		this->del_el();
		b = head->var;
		this->del_el();
		this->push(a + b);
	}
	void sub() {
		int a, b;
		a = head->var;
		this->del_el();
		b = head->var;
		this->del_el();
		this->push(a - b);
	}
	void mul() {
		int a, b;
		a = head->var;
		this->del_el();
		b = head->var;
		this->del_el();
		this->push(a * b);
	}
	void div() {
		int a, b;
		a = head->var;
		this->del_el();
		b = head->var;
		this->del_el();
		this->push(a / b);
	}
	void print() {
		Node* node;
		node = tail;
		printf("tail>>>  ");
		while (node != nullptr) {
			printf("%d%s", node->var, " ");
			node = node->next;
		}
		printf(" <<<head \n");
	}
};
int tree();

int main(){
    Stack stack;
	stack.push(3);
	stack.print();
    system("pause");


	stack.push(5);
	stack.print();
    system("pause");
  goto label;
    int i; 
    i = stack.pop();
	stack.print();
    system("pause");
	stack.push(56);
	stack.print();
    system("pause");

    stack.pop();
	stack.print();
    system("pause");

label:

	stack.push(15);
	stack.print();
    system("pause");
	stack.push(7);
	stack.print();
    system("pause");
    stack.add();
	stack.print();
    system("pause");

    cout << stack.pop() << endl;
    system("pause");
    return 0;
}

int tree(){
    Stack stack;
	stack.push(5);
	stack.print();
    system("pause");


    return stack.pop();
}

