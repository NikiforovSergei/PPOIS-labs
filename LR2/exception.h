#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <exception>
#include <string>

namespace xml
{
	class EasyXmlException : std::exception
	{
	public:
		EasyXmlException(const std::string& msg, int errorCode = 0, unsigned int lineNumber = 0);
		~EasyXmlException() throw ();

		const char* what() const throw();

		int getErrorCode() const;
		unsigned int getLineNumber() const;

	private:
		std::string message_;
		const int errorCode_;
		const unsigned int lineNumber_;
	};
}

#endif
