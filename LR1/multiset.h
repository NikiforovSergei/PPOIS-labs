#ifndef MULTISET_H
#define MULTISET_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


namespace custom_multiset {

	class multiset {

	private:

		vector<string> set;

		string get_elem(string);

		int get_coeff(string);

	public:

		multiset(vector<string>);

		void set_container(vector<string>);

		string get_set_string();

		vector<string> operator + (multiset const& obj);

		vector<string> operator - (multiset const& obj);

		vector<string> operator * (multiset const& obj);

		bool operator == (multiset& obj);

		bool operator != (multiset& obj);

		istream& operator >> (istream&);

		ostream& operator << (ostream&);

		vector<string> set_add(string);

		vector<string> set_remove(string);

		vector<string> set_union(vector<string>, vector<string>);

		vector<string> set_intersection(vector<string>, vector<string>);

		vector<string> set_difference(vector<string>, vector<string>);

		bool operator [] (string const& obj);

		bool set_inclusion(string);

		bool is_empty();

		int set_length();

		void print();

	};
}

#endif // SET_H
