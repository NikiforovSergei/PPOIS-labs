#include <iostream>

#include "XMLDocument.hpp"

int main() {
	auto* doc = new XMLDocument("test_for_lab.xml");

	doc->parse();
	doc->print("test_3.txt");
	XMLElement* root = doc->get_first_child();

	std::cout << (root->get_name()) << std::endl;
	std::cout << (root->get_first_child()->get_name()) << std::endl;
	std::cout << (root->get_first_child()->get_pc_data()) << std::endl;
	std::cout << (root->get_first_child()->get_next_sibling()->get_name()) << std::endl;
	bool fact = root->get_first_child()->has_attributes();
	std::cout << fact << endl;
	std::cout << root->get_first_child()->get_name();
}