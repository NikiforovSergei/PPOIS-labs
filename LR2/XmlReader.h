#pragma once

#include <fstream>
#include <stack>
#include <iostream>
#include <string>
#include <tuple>

#include "Document.h"
#include "ProcessingInstruction.h"
#include "TextElement.h"

namespace XML
{
	/// <summary>
	/// Reads from the given XML-File, analyzes, filters and builds a XML-Document.
	/// </summary>
	class XmlReader
	{
	public:
		/// <summary>
		/// Creates a new XmlReader instance.
		/// </summary>
		XmlReader(std::ifstream *file);
		/// <summary>
		/// Launches the process of reading and building an element tree. 
		/// </summary>
		void ReadAndDissasemble();
		Document* document;
	private:
		std::ifstream *inputFile;
		std::stack<TagElement*> tagStack;
		bool currentFileRead;
		int currentLine;

		TagElement* ProcessLineToTagElement(std::string content) const;
		void GetToNextCharacter();
		void AnalyzeCharacters();
		void AnalyzeNonTextElement();
		void AnalyzePI();
		void AnalyzeOpeningTag();
		void AnalyzeClosingTag();
		void AnalyzeText();
		void AnalyzeComment();
		void PushPointer();
		std::string ReturnStringUntilSymbol(char symbol);
	};
}