#include "functions.h"
#include "exception.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <stack>
#include <cstring>

namespace xml
{
	const std::string esc_sequences[] = {"&amp;", "&lt;", "&gt;", "&apos;", "&quot;"};
	const std::string esc_values[] = {"&", "<", ">", "'", "\""};

	Node* loadXml(const std::string& filePath)
	{
		std::ifstream reader(filePath.c_str());

		if (reader.is_open())
		{
			std::stack<Node*> ancestors;
			Node* root = NULL;

			std::string line;
			std::string value = "";
			unsigned int lineNumber = 0;

			// read file line by line
			while (getline(reader, line))
			{
				lineNumber++;
				size_t index = 0;


				while (index < line.length())
				{
					size_t openIndex = line.find('<', index);
					size_t closeIndex = line.find("</" , index, 2);
					const size_t notFound = std::string::npos;

					if (openIndex == notFound && closeIndex == notFound)
					{ 
						// the rest of this line is probably a value so save it
						value += line.substr(index);
						index = line.length();
					}
					// Check if this is an opening tag.
					else if (openIndex < closeIndex || closeIndex == notFound)
					{ 
						std::string name = getElementName(line, openIndex + 1);

						// Make sure the tag is not empty.
						if (name.length() == 0)
						{
							throw EasyXmlException("No name in opening tag on line %d.", 9, lineNumber);
						}
						// Check if the tag is a comment.
						else if (name.length() >= 3 && name.substr(0, 3) == "!--")
						{
							std::string comment;

							size_t endIndex = openIndex + 4; // Index of comment close.
							size_t startIndex = endIndex; // Index to start search (after "!--")
							const unsigned int origLineNumber = lineNumber; // Save the line number of the opening tag.

							// If the end of the comment is not on this line, we must keep searching.
							while ( (endIndex = line.find("-->", startIndex)) == notFound )
							{
							
								comment += line.substr(startIndex) + "\n";

								// Reset startIndex to the beginning of the new line.
								startIndex = 0; 

								if (!getline(reader, line))
								{
									throw EasyXmlException("Unclosed comment at line %d.", 8, origLineNumber);
								}

								lineNumber++;
							}

							comment += line.substr(startIndex, endIndex - startIndex);

							index = endIndex + 3;

							
						}
						// Check if the tag is an xml Prolog.
						else if (name.length() >= 4 && name.substr(0, 4) == "?xml")
						{
							if (lineNumber != 1)
							{
								throw EasyXmlException("XML Prolog must appear on the first line." \
								                       " Prolog found on line %d.", 6, lineNumber);
							}

							if (name[name.length() - 1] != '?')
							{
								throw EasyXmlException("Malformed XML Prolog. Must end with \"?>\" instead" \
								                       " of \">\" at line %d.", 7, lineNumber);
							}

							
							index = openIndex + 1 + name.length() + 1;

						
						}
						// It must be a node.
						else
						{
							bool isSelfClosing = (name[name.length() - 1] == '/');

							 // Check for attributes
							 int attrIndex = 0;
							 while ((attrIndex = name.find(" ", attrIndex)) != notFound)
							 {
							 	name = name.substr(0, attrIndex);
							 	break;
							 }

							Node* newNode = new Node(name);

							if (isSelfClosing)
							{
								std::string temp = name.substr(0, name.length() - 1);
								newNode->name = rtrim(temp);
							}

							if (!ancestors.empty())
							{

								ancestors.top()->value += value;
								value = "";
								ancestors.top()->children.push_back(newNode);
								ancestors.top()->sortedChildren.insert(newNode);
							}
							else
							{
								if (root != NULL)
								{
									throw EasyXmlException("Malformed XML: Multiple root nodes found." \
										" First root node is \"" + root->name + "\", second node is \"" + \
										newNode->name + "\" defined at line %d.", 2, lineNumber);
								}

								root = newNode;
							}

							// If the tag is self closing, do not push it since it will have no closing tag.
							if (!isSelfClosing)
							{
								ancestors.push(newNode);
							}

							index = openIndex + 1 + name.length() + 1;
						}
					}
					// Closing tag.
					else
					{
						std::string elementName = getElementName(line, closeIndex + 2);

						if (ancestors.top() == root && root->name != elementName)
						{
							throw EasyXmlException("Malformed XML: No opening tag for \"" + 
								elementName + "\", closing tag found at line %d.", 3, lineNumber);
						}

						if (ancestors.top()->name != elementName)
						{
							throw EasyXmlException("Malformed XML: Mismatched closing tag at line %d." \
								" Expected \"" + ancestors.top()->name + "\" found \"" + elementName + "\"." \
								, 5, lineNumber);
						}


						value += line.substr(index, openIndex - index);

						// Replace XML escape sequences. Ampersands must be replaced last or else they may
						// cause other escape sequences to be replaced that were not in the original string.
						for (int i = 4; i >= 0; i--)
						{
							replaceAll(value, esc_sequences[i], esc_values[i]);
						}

						ancestors.top()->value += value;
						value = "";

						index = closeIndex + 2 + ancestors.top()->name.length() + 1;
						ancestors.pop();
					}
				}
			}

			if (root == NULL)
			{
				throw EasyXmlException("No XML elements found in file \"" + filePath + "\".", 1);
			}

			if (!ancestors.empty())
			{
				throw EasyXmlException("Unclosed XML element \"" + ancestors.top()->name + "\".", 4);
			}

			reader.close();

			return root;
		}
		else
		{
			throw EasyXmlException("Unable to open file \"" + filePath + "\".", 101);
			return NULL;
		}
	}

	void saveXml(const Node* node, const std::string& filePath)
	{
		std::ofstream file;
		file.open(filePath.c_str());
		saveXml(node, file);
		file.close();
	}

	void saveXml(const Node* node, std::ostream& out, std::string indentation)
	{
		out << indentation << "<" << node->name;

		if (node->children.size() > 0)
		{
			out << ">\n";

			for (std::vector<Node*>::const_iterator it = node->children.begin();
			     it != node->children.end();
			     ++it)
			{
				saveXml(*it, out, indentation + "\t");
			}

			out << indentation << "</" << node->name << ">";
		}
		else if (node->value == "")
		{
			out << " />";
		}
		else
		{
			std::string value(node->value);
			for (int i = 0; i < 5; i++)
			{
				replaceAll(value, esc_values[i], esc_sequences[i]);
			}

			out << ">" << value;
			out << "</" << node->name << ">";
		}

		out << "\n";
	}

	void printTree(const Node* node, std::string indentation)
	{
		std::cout << indentation << node->name << ": " << node->value << std::endl;

		// increase the indentation for the next level
		indentation += "\t";

		
		for (std::vector<Node *>::const_iterator it = node->children.begin();
		     it != node->children.end();
		     it++)
		{
			printTree((*it), indentation);
		}
	}

	void deleteTree(Node* node)
	{
		if (node == NULL)
		{
			throw EasyXmlException("deleteTree was called on a NULL pointer.", 102);
		}
		else
		{
			std::vector<Node*>::iterator it;
			for (it = node->children.begin(); it != node->children.end(); ++it)
			{
				deleteTree(*it);
			}

			delete node;
		}
	}

	std::string getElementName(const std::string& data, size_t startIndex)
	{
		return data.substr(startIndex, data.find(">", startIndex) - startIndex);
	}


	// trim from start
	std::string& ltrim(std::string &s)
	{
			s.erase(s.begin(), std::find_if(s.begin(), s.end(),
				[](unsigned char ch) {return !std::isspace(ch); }));
		return s;
	}

	// trim from end
	std::string& rtrim(std::string &s)
	{
			s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {return !std::isspace(ch); }).base(), s.end());
		
		return s;
	}

	// trim from both ends
	std::string& trim(std::string &s)
	{
		return ltrim(rtrim(s));
	}

	void replaceAll(std::string& str, const char* from, const std::string& to)
	{
		if (strlen(from) == 0)
		{
			return;
		}

		std::string newStr;
		newStr.reserve(str.length());

		size_t start_pos = 0, pos;
		while ((pos = str.find(from, start_pos)) != std::string::npos)
		{
			newStr += str.substr(start_pos, pos - start_pos);
			newStr += to;
			start_pos = pos + strlen(from);
		}
		newStr += str.substr(start_pos);
		str.swap(newStr);
	}

	void replaceAll(std::string& str, const std::string& from, const std::string& to)
	{
		replaceAll(str, from.c_str(), to);
	}
}
