#include <iostream>
#include "easyXml.h"


int main()
{
	/*** LOADING FILES  *************************************************************************************/

	xml::Node* root = NULL;

	try
	{
		
		root = xml::loadXml("example.txt");
	}
	catch (const xml::EasyXmlException& e)
	{
		// Print out the error message.
		std::cout << e.what();
	}

	if (root != NULL)
	{
		/*** PRINTING THE STRUCTURE *************************************************************************/

		// You can print the XML structure in a readable format.
		std::cout << "Printing the XML structure..." << std::endl;
		xml::printTree(root);
		std::cout << std::endl;
		xml::saveXml(root, "example_output.txt");
		xml::deleteTree(root);
	}

	return 0;
}