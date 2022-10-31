#pragma once
#include <iostream>
#include <vector>
#include "Set.h"

class Operation
{
public:
	static Set set_union(Set& set1, Set& set2);
	static Set set_traversal(Set& set1, Set& set2);
	static Set set_symmetric_difference(Set& set1, Set& set2);
	static Set set_boolean(Set& set);
private:
	static Set set_difference(Set& set1, Set& set2);
};

