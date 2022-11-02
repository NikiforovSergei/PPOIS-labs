#ifndef NODE_H
#define NODE_H


#include "exception.h"
#include <set>
#include <vector>
#include <string>

namespace xml
{
	class Node
	{
	public:
		Node();
		Node(const char* name, const char* value = NULL);
		Node(const std::string& name, const std::string& value = "");
		Node(const Node& rhs);
		Node& operator=(const Node& rhs);

		std::string val() const;
		// Templated short-hand "getter" function
		template <class T> T val() const;

		std::string name;
		std::string value;

		std::vector<Node*> children; // for preserving order and duplicate xml nodes
		std::set<Node*, bool (*)(const Node*, const Node*)> sortedChildren;

	private:
		// Comparator function used to sort the "children" set.
		static bool node_ptr_compare(const Node* lhs, const Node* rhs)
		{
			return lhs->name < rhs->name;
		}
	};
}

#endif
