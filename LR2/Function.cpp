#include <iostream>
#include <vector>
#include "Function.h"


Set Operation::set_union(Set& set1, Set& set2) {
	std::vector<char> buf_ch_vec1 = set1.get_char_vector();
	std::vector<Set> buf_set_vec1 = set1.get_set_vector();
	std::vector<char> buf_ch_vec2 = set2.get_char_vector();
	std::vector<Set> buf_set_vec2 = set2.get_set_vector();
	Set* buf_set = new Set();

	for (size_t i = 0; i < buf_ch_vec1.size(); i++) {
		buf_set->add_elements(buf_ch_vec1[i]);
	}
	for (size_t i = 0; i < buf_ch_vec2.size(); i++) {
		if (std::find(buf_ch_vec1.begin(), buf_ch_vec1.end(), buf_ch_vec2[i]) == buf_ch_vec1.end())
			buf_set->add_elements(buf_ch_vec2[i]);
	}
	if (buf_set_vec1.size() != 0 || buf_set_vec2.size() != 0) {
		for (size_t i = 0; i < buf_set_vec1.size(); i++) {
			buf_set->add_set(buf_set_vec1[i]);
		}
		for (size_t i = 0; i < buf_set_vec2.size(); i++) {
			if (std::find(buf_set_vec1.begin(), buf_set_vec1.end(), buf_set_vec2[i]) == buf_set_vec1.end())
				buf_set->add_set(buf_set_vec2[i]);
		}
	}
	return *buf_set;
}

Set Operation::set_traversal(Set& set1, Set& set2) {
	std::vector<char> buf_ch_vec1 = set1.get_char_vector();
	std::vector<Set> buf_set_vec1 = set1.get_set_vector();
	std::vector<char> buf_ch_vec2 = set2.get_char_vector();
	std::vector<Set> buf_set_vec2 = set2.get_set_vector();
	Set* buf_set = new Set();

	for (size_t i = 0; i < buf_ch_vec1.size(); i++) {
		for (size_t j = 0; j < buf_ch_vec2.size(); j++) {
			if (buf_ch_vec1[i] == buf_ch_vec2[j])
				buf_set->add_elements(buf_ch_vec1[i]);
		}
	}
	if (buf_set_vec1.size() != 0 && buf_set_vec2.size() != 0) {
		for (size_t i = 0; i < buf_set_vec1.size(); i++) {
			for (size_t j = 0; j < buf_set_vec2.size(); j++) {
				if (buf_set_vec1[i] == buf_set_vec2[j])
					buf_set->add_set(buf_set_vec1[i]);
			}
		}
	}
	return *buf_set;
}

Set Operation::set_symmetric_difference(Set& set1, Set& set2) {
	Set buf_set1 = Operation::set_difference(set1, set2);
	Set buf_set2 = Operation::set_difference(set2, set1);
	return Operation::set_union(buf_set1, buf_set2);
}

Set Operation::set_difference(Set& set1, Set& set2) {
	std::vector<char> buf_ch_vec1 = set1.get_char_vector();
	std::vector<Set> buf_set_vec1 = set1.get_set_vector();
	std::vector<char> buf_ch_vec2 = set2.get_char_vector();
	std::vector<Set> buf_set_vec2 = set2.get_set_vector();
	Set* buf_set = new Set();

	for (size_t i = 0; i < buf_ch_vec2.size(); i++) {
		auto it = std::find(buf_ch_vec1.begin(), buf_ch_vec1.end(), buf_ch_vec2[i]);
		if (it != buf_ch_vec1.end())
			buf_ch_vec1.erase(it);
	}
	for (size_t i = 0; i < buf_ch_vec1.size(); i++)
		buf_set->add_elements(buf_ch_vec1[i]);
	if (buf_set_vec1.size() != 0) {
		for (size_t i = 0; i < buf_set_vec2.size(); i++) {
			auto it = std::find(buf_set_vec1.begin(), buf_set_vec1.end(), buf_set_vec2[i]);
			if (it != buf_set_vec1.end())
				buf_set_vec1.erase(it);
		}
		for (size_t i = 0; i < buf_set_vec1.size(); i++)
			buf_set->add_set(buf_set_vec1[i]);
	}
	return *buf_set;
}

Set Operation::set_boolean(Set& set) {
	std::vector<char> buf_ch_vec = set.get_char_vector();
	std::vector<Set> buf_set_vec = set.get_set_vector();
	Set* buf_set = new Set;

	for (size_t i = 1; i < buf_ch_vec.size(); i++) {
		for (size_t j = 0; j < buf_ch_vec.size(); j++) {
			Set buf;
			for (size_t k = j; k < buf_ch_vec.size(); k++) {
				if (buf.get_char_vector().size() == i)
					break;
				else
					buf.add_elements(buf_ch_vec[k]);
			}
			buf_set->add_set(buf);
		}
	}
	buf_set->add_set(set);
	return *buf_set;
}
