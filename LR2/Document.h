#pragma once

#include <vector>
#include <iostream>

#include "TagElement.h"
#include "Comment.h"
#include "ProcessingInstruction.h"

namespace XML
{
	/// <summary>
	/// XML document that contains a tree of elements.
	/// </summary>
	class Document
	{
	public:
		/// <summary>
		/// Creates a new Document instance.
		/// </summary>
		Document();
		TagElement *root;
		std::vector<Comment> comments;
		ProcessingInstruction *PI;
	};
}
