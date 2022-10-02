#include "XmlPrinter.h"

XML::XmlPrinter::XmlPrinter(Document* document, std::ofstream* out)
{
	this->document = document;
	this->outputFile = out;
	this->tabAmount = 0;
}

void XML::XmlPrinter::Print()
{
	outputFile->clear();
	*outputFile << document->PI->value << "\n";
	PrintElement(document->root);
}

void XML::XmlPrinter::PrintElement(Element* element)
{
	if (element->children.size() > 0)
	{
		bool hasOneTextChild = (element->children.size() == 1 && element->children[0]->children.size() == 0);
		PrintOpeningTag(element, hasOneTextChild);
		for (auto* child : element->children)
			PrintElement(child);
		PrintClosingTag(element, hasOneTextChild);
	}
	else
	{
		*outputFile << element->GetValueWStringArray()[0];
		if (element->GetValueWStringArray()[0][0] == '<')
		{
			*outputFile << std::endl;
			PrintTabs(tabAmount-1);
		}
	}
}

void XML::XmlPrinter::PrintTabs(int tabAmount)
{
	for (int i = 0; i < tabAmount; i++)
	{
		*outputFile << "\t";
	}
}

void XML::XmlPrinter::PrintOpeningTag(Element *element, bool hasOneTextChild)
{
	*outputFile << element->GetValueWStringArray()[0];
	if (!hasOneTextChild)
	{
		tabAmount++;
		*outputFile << std::endl;
		PrintTabs(tabAmount);
	}
}

void XML::XmlPrinter::PrintClosingTag(Element* element, bool hasOneTextChild)
{
	if (!hasOneTextChild)
		tabAmount--;
	*outputFile << element->GetValueWStringArray()[1];
	if (element->parent != nullptr)
	{
		*outputFile << std::endl;
		if (element->parent->children.back() == element)
			PrintTabs(tabAmount - 1);
		else
			PrintTabs(tabAmount);
	}
}

//void XML::XmlPrinter::PrintTextElement(Element* element)
//{
//	if (element->children.size() > 0)
//		*outputFile << "</" << element->value << ">\n";
//}