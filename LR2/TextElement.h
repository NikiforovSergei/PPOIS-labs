#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "Element.h"
#include "TagElement.h"

namespace XML
{
	/// <summary>
	/// Element with it's value being a text. Can't have child elements.
	/// </summary>
	class TextElement : public Element
	{
	public:
		/// <summary>
		/// Creates a new TextElement instance.
		/// </summary>
		/// <param name="value">TextElement's text.</param>
		/// <param name="parent">TextElement's parent element.</param>
		TextElement(std::string value, TagElement *parent);
		/// <summary>
		/// Returns element's content and attributes as a string array.
		/// </summary>
		/// <returns>String array where first element is it's value and other elements are attributes.</returns>
		std::string* GetValueWStringArray() const override;
	};
}

