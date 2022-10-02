#include <string>

namespace XML
{
	/// <summary>
	/// Comments left by and to xml-file developers.
	/// </summary>
	class Comment
	{
	public:
		/// <summary>
		/// Creates new Comment instance.
		/// </summary>
		/// <param name="value">Comment's content.</param>
		Comment(std::string value);
		std::string value;
	};
}