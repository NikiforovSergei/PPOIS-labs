#include <iostream>
#include"parser.h"
#include"path.h"

int main(int argc, char* argv[])
{
	using namespace xml;
	std::ifstream in;
	std::string file_name = "XML.xml";
	in.open(file_name);
	std::ofstream txtFile;
	Parser reader(&in);
	reader.process();
	std::string search_request = "/bookstore/book/title[!attr(“lang”, “en”) && text(“Learn XML”)]";
	Searcher p(reader.document, search_request);
	p.parse();
	int i = 1;
	auto requests = p.get_result();
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
