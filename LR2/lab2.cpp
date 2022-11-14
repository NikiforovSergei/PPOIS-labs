#include <iostream>
#include "parser.h"
#include "path.h"

int main(int argc, char* argv[])
{
	using namespace xml;
	std::ifstream in;
	std::string file_name;
	std::cout<< "Enter  file name\n";
	std::cin >> file_name;
	std::cin.ignore();
	in.open(file_name);
	std::ofstream txtFile;
	Parser reader(&in);
	reader.process();
	std::string search_request;
	std::cout<< "Enter search request\n";
	std::getline(std::cin, search_request);
	Searcher finder(reader.document, search_request);
	finder.parse();
	int i = 1;
	auto requests = finder.get_result();
	if (requests.empty()) std::cout << "Nothing founded";
	else
		for (auto node : requests) {
			std::cout << i++ << " element:\nName: " << node->value << "\n" << "Text: " << node->getText()
				<< "\nAttributes: ";
			for (auto attribute : node->getAttributes()) {
				std::cout << attribute.getName() << " = " << attribute.getValue();
			}
			std::cout << "\n\n";
		}

	return 0;
}
