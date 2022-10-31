#pragma once
#include<iostream>
#include<vector>

//! Node structure of doubly linked list 
/*The structure contains:
node value 
 pointer to next node 
 pointer to previous node 
*/
struct Node {
	char value;
	Node* next = NULL;
	Node* prev = NULL;
};

//! Rule structure 
/*The structure contains 
 the value of nodes which you need to replace
 the value you want to chage to
 caret movement direction 
 number of the rule you want to go
*/
struct Rule {
	char start;
	char end;
	char direction;
	int status;
};

/*The main class in which the Turing machine is implemented
 Tape of this machine is realized with a doubly linked list
 Class has methodes that realized the rules which are needing for a Turing mashine to work
*/
class Turing {
public:
	Node* head = NULL;

	//! A method add_element 
	/*
	This method add elemnts to a doubly linked list 
	Method takes one value - the value of the node
	*/
	void add_element(char value);

	//! A method show_element
	/* 
	This method show elements of a doubly linked list
	*/
	void show_element();

	//! A method run
	/*! 
	This method used to enter rules
	Method takes two value: 
	*/
	void run(std::vector<Rule> &rules, int size);

	//! A method analyze_rule
	/*
	This method starts the Turing mashine: structure vector of rules and size of this vector 
	*/
	void analyze_rule(std::vector<Rule> &rules, int number, Turing turing, bool log);

	//! A method breakpoint
	/*
	This method sets the caret to one of the elements of a doubly linked list
	Method takes three value: structure vector of rules, the node which will be assigned next head and class Turing 
	*/
	void breakpoint(int number, Node* &buf, Turing turing);

	//! A method tape
	/*
	This method creates a tape of size tracks
	Method takes oen value - the size of the tape
	*/
	void tape(int size);

	//! A method show_rules
	/* 
	This method show rules
	Method takes two value: structure vector of rules and the size of this vector
	*/
	void show_rules(std::vector<Rule>& rules, int size);

	//! A method change_rule
	/* 
	This method makes a peplacement of one of the rules
	Method takes two value: structure vector of rules and the number of rules, which you need to replace
	*/
	void change_rule(std::vector<Rule>& rules, int change);

	//! A method delete_rule
	/*
	This method delete one of the rules
	Method takes two value: structure vector of rules and the number of rules, which you need to delete
	*/
	void delete_rule(std::vector<Rule>& rules, int number);

	void run_in_file(std::vector<Rule>& rules, int size, const char* path);

private:
	Node* tail = NULL;

	//! A method delete_element
	/*!  
	This method delete elements of a doubly linked list
	Method takes one value - the node which you want to delete
	*/
	void delete_element(Node* buf);

	//! A method right_shift
	/*!
	This method moves caret to the right
	Method takes one value - node which will become predeccesor of this node
	*/
	void right_shift(Node* &buf);

	//! A method left_shift
	/*!  
	This method moves caret to the left
	Method takes one value - node which will become next of this node
	*/
	void left_shift(Node* &buf);

	//! A method change_element
	/*!
	This method change the value of node 
	Method taks two value: node which value you need to replace and new value of this node 
	*/
	void change_element(Node* &buf, char value);
};