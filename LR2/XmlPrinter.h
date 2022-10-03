#pragma once

#include <fstream>
#include <stack>
#include <iostream>
#include <string>

#include "Document.h"
#include "ProcessingInstruction.h"
#include "TextElement.h"

namespace XML
{
	/// <summary>
	/// Prints XML-document to a file by processing document's element tree.
	/// </summary>
	class XmlPrinter
	{
	public:
		/// <summary>
		/// Creates a new XmlPrinter instance.
		/// </summary>
		/// <param name="document">Document to print.</param>
		/// <param name="out">File to print to.</param>
		XmlPrinter(Document *document, std::ofstream *out);
		/// <summary>
		/// Launches the full process of printing.
		/// </summary>
		void Print();
	private:
		std::ofstream* outputFile;
		Document* document;
		int tabAmount;

		void PrintElement(Element* element);
		void PrintTabs(int tabAmount);

		void PrintOpeningTag(Element* element, bool hasOneTextChild);
		void PrintClosingTag(Element* element, bool hasOneTextChild);
	};
}