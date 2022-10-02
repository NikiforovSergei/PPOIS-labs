#pragma once

#include <string>

namespace XML
{
	/// <summary>
	/// Tag attribute.
	/// </summary>
	class Attribute
	{
	public:
		/// <summary>
		/// Creates a new Attribute instance.
		/// </summary>
		/// <param name="name">Attribute's name.</param>
		/// <param name="value">Attrubute's value.</param>
		Attribute(std::string name, std::string value);
		std::string name;
		std::string value;
	};
}