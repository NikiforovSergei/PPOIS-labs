#pragma once

#include <vector>
#include <string>

#include "Attribute.h"

namespace XML
{
	/// <summary>
	/// Virtual class that represents general idea of an XML-Element.
	/// </summary>
	class Element
	{
	public:
		/// <summary>
		/// Creates a new Element instance.
		/// </summary>
		/// <param name="parent">Element's parent element. Null if root.</param>
		/// <param name="value">Element's content.</param>
		Element(Element *parent, std::string value);
		/// <summary>
		/// Returns element's content and attributes as a string array.
		/// </summary>
		/// <returns>String array where first element is it's value and other elements are attributes.</returns>
		virtual std::string* GetValueWStringArray() const = 0;

		Element *parent;
		std::string value;
		std::vector<Element*> children{};
	};
}

