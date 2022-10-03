#pragma once

#include <string>

namespace XML
{
	/// <summary>
	/// Settings line in the beggining of every XML-Document.
	/// </summary>
	class ProcessingInstruction
	{
	public:
		std::string value;
	};
}