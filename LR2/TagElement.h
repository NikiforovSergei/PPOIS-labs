#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "Element.h"


namespace XML
{
	/// <summary>
	/// Element that can have child elements and attributes.
	/// </summary>
	class TagElement : public Element
	{
	public:
		/// <summary>
		/// Creates a new TagElement instance.
		/// </summary>
		/// <param name="value">TagElement's value.</param>
		/// <param name="attributes">Vector of TagElement's attributes and their values.</param>
		/// <param name="parent">TagElement's parent.</param>
		TagElement(std::string value, std::vector<Attribute> attributes, TagElement *parent);
		/// <summary>
		/// Returns element's content and attributes as a string array.
		/// </summary>
		/// <returns>String array where first element is it's value and other elements are attributes.</returns>
		std::string* GetValueWStringArray() const override;

		std::vector<Attribute> attributes;
	};
}

